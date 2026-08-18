#include "reaction.h"
#include <stdlib.h>
#include <math.h>

static float en_diff(const Element *a, const Element *b)
{
    // treat undefined EN (0.0f, mostly noble gases / superheavies) as "no bond tendency"
    if (a->electronegativity <= 0.0f || b->electronegativity <= 0.0f)
        return 0.0f;
    return fabsf(a->electronegativity - b->electronegativity);
}

static int is_metal(Family f)
{
    return f == FAM_ALKALI || f == FAM_ALKALINE_EARTH || f == FAM_TRANSITION ||
           f == FAM_LANTHANIDE || f == FAM_ACTINIDE || f == FAM_POST_TRANSITION;
}

static int either_is(const Element *a, const Element *b, Family f)
{
    return a->family == f || b->family == f;
}

static int both_are(const Element *a, const Element *b, Family f)
{
    return a->family == f && b->family == f;
}

static int pair_has(const Element *a, const Element *b, Family f1, Family f2)
{
    return (a->family == f1 && b->family == f2) || (a->family == f2 && b->family == f1);
}

// water-group nonmetals: reacting violently with alkali/alkaline-earth metals
static int is_water_group(const Element *e)
{
    return e->atomic_number == 8 || e->atomic_number == 1; // O, H
}

ReactionType reaction_classify(const Element *a, const Element *b)
{
    // same element: nothing interesting happens
    if (a->atomic_number == b->atomic_number)
        return REACT_NONE;

    // noble gases are inert against everything
    if (either_is(a, b, FAM_NOBLE_GAS))
        return REACT_NONE;

    float diff = en_diff(a, b);
    int metal_nonmetal_pair = (is_metal(a->family) && !is_metal(b->family)) ||
                               (is_metal(b->family) && !is_metal(a->family));

    // alkali metal + halogen: textbook violent reaction
    if (pair_has(a, b, FAM_ALKALI, FAM_HALOGEN))
        return REACT_EXPLODE;

    // alkali/alkaline-earth metal + water-group element (O, H): fizz or explode
    if ((either_is(a, b, FAM_ALKALI) || either_is(a, b, FAM_ALKALINE_EARTH)) &&
        (is_water_group(a) || is_water_group(b)))
    {
        // alkali metals go further than alkaline-earth in reactivity
        return either_is(a, b, FAM_ALKALI) ? REACT_EXPLODE : REACT_FIZZ;
    }

    // halogen + nonmetal or metalloid: chance of toxic gas byproduct
    if (either_is(a, b, FAM_HALOGEN) &&
        (either_is(a, b, FAM_NONMETAL) || either_is(a, b, FAM_METALLOID)))
        return REACT_TOXIC_GAS;

    // large electronegativity gap + metal/nonmetal split -> ionic bond
    if (metal_nonmetal_pair && diff >= 1.7f)
        return REACT_PRECIPITATE;

    if (metal_nonmetal_pair && diff >= 0.8f)
        return REACT_COLOR_CHANGE;

    // two nonmetals (or metalloids) with a small EN gap -> mild covalent blend
    if (!is_metal(a->family) && !is_metal(b->family) && diff < 0.8f)
        return REACT_COLOR_CHANGE;

    // same family or very similar electronegativity: not much happens
    if (a->family == b->family || diff < 0.4f)
        return REACT_NONE;

    // transition metals together: mild color shift (alloy-like)
    if (both_are(a, b, FAM_TRANSITION))
        return REACT_COLOR_CHANGE;

    return REACT_NONE;
}


static Color lerp_color(Color a, Color b, float t)
{
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    Color out;
    out.r = (unsigned char)(a.r + (b.r - a.r) * t);
    out.g = (unsigned char)(a.g + (b.g - a.g) * t);
    out.b = (unsigned char)(a.b + (b.b - a.b) * t);
    out.a = 255;
    return out;
}

static float jitter(float base, float spread)
{
    // random factor in [-spread, +spread], applied on top of a deterministic base
    float r = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    return base + r * spread;
}

ReactionResult reaction_compute(const Element *a, const Element *b)
{
    ReactionResult result;
    result.type = reaction_classify(a, b);
    result.description = reaction_type_description(result.type);

    switch (result.type)
    {
    case REACT_NONE:
        result.intensity = 0.0f;
        result.result_color = lerp_color(a->base_color, b->base_color, 0.5f);
        result.particle_count = 0;
        break;

    case REACT_COLOR_CHANGE:
        result.intensity = jitter(0.3f, 0.1f);
        result.result_color = lerp_color(a->base_color, b->base_color, 0.5f);
        result.particle_count = 12;
        break;

    case REACT_FIZZ:
        result.intensity = jitter(0.45f, 0.1f);
        result.result_color = lerp_color(a->base_color, b->base_color, 0.6f);
        result.particle_count = 40;
        break;

    case REACT_PRECIPITATE:
        result.intensity = jitter(0.4f, 0.1f);
        result.result_color = lerp_color(a->base_color, b->base_color, 0.35f);
        result.particle_count = 24;
        break;

    case REACT_TOXIC_GAS:
        result.intensity = jitter(0.6f, 0.15f);
        result.result_color = (Color){140, 200, 60, 200}; 
        result.particle_count = 90;
        break;

    case REACT_EXPLODE:
        result.intensity = jitter(0.9f, 0.15f);
        if (result.intensity > 1.0f) result.intensity = 1.0f;
        result.result_color = (Color){255, 140, 0, 255}; 
        result.particle_count = 200; 
        break;

    default:
        result.intensity = 0.0f;
        result.result_color = WHITE;
        result.particle_count = 0;
        break;
    }

    if (result.intensity < 0.0f) result.intensity = 0.0f;

    return result;
}

const char *reaction_type_description(ReactionType type)
{
    switch (type)
    {
    case REACT_NONE:
        return "No significant reaction.";
    case REACT_COLOR_CHANGE:
        return "Mild reaction: color shift observed.";
    case REACT_FIZZ:
        return "Effervescent reaction: bubbling and gas release.";
    case REACT_PRECIPITATE:
        return "Ionic bond forms: solid precipitate settles out.";
    case REACT_TOXIC_GAS:
        return "Hazardous reaction: toxic gas produced.";
    case REACT_EXPLODE:
        return "Violent reaction: explosive release of energy.";
    default:
        return "Unknown reaction.";
    }
}