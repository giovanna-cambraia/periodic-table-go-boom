#include "particles.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846f

ParticleSystem particles_init(void)
{
    ParticleSystem ps;
    ps.count = 0;
    for (int i = 0; i < MAX_PARTICLES; i++)
        ps.particles[i].active = 0;
    return ps;
}

static float rand_range(float lo, float hi)
{
    float t = (float)rand() / (float)RAND_MAX;
    return lo + t * (hi - lo);
}

// intensity-driven speed/life/size envelope, shared by all reaction types
// so REACT_FIZZ vs REACT_EXPLODE feel categorically different, not just
// "same burst, more particles"
static void particle_profile_for(ReactionType type, float intensity,
                                  float *speed_min, float *speed_max,
                                  float *life_min, float *life_max,
                                  float *radius_min, float *radius_max)
{
    switch (type)
    {
    case REACT_FIZZ:
        *speed_min = 10.0f;  *speed_max = 40.0f + intensity * 20.0f;
        *life_min = 0.6f;    *life_max = 1.2f;
        *radius_min = 1.5f;  *radius_max = 3.0f;
        break;

    case REACT_TOXIC_GAS:
        *speed_min = 5.0f;   *speed_max = 20.0f + intensity * 15.0f;
        *life_min = 1.2f;    *life_max = 2.2f;
        *radius_min = 4.0f;  *radius_max = 9.0f;
        break;

    case REACT_PRECIPITATE:
        *speed_min = 15.0f;  *speed_max = 35.0f;
        *life_min = 0.8f;    *life_max = 1.4f;
        *radius_min = 2.0f;  *radius_max = 4.0f;
        break;

    case REACT_EXPLODE:
        *speed_min = 80.0f + intensity * 60.0f;
        *speed_max = 160.0f + intensity * 140.0f;
        *life_min = 0.4f;    *life_max = 0.9f;
        *radius_min = 2.0f;  *radius_max = 5.0f;
        break;

    case REACT_COLOR_CHANGE:
    case REACT_NONE:
    default:
        *speed_min = 5.0f;   *speed_max = 15.0f;
        *life_min = 0.5f;    *life_max = 0.9f;
        *radius_min = 1.0f;  *radius_max = 2.0f;
        break;
    }
}

void particles_spawn_burst(ParticleSystem *ps, Vector2 origin, const ReactionResult *result)
{
    if (!ps || !result)
        return;

    if (result->particle_count <= 0)
        return;

    float speed_min, speed_max, life_min, life_max, radius_min, radius_max;
    particle_profile_for(result->type, result->intensity,
                          &speed_min, &speed_max, &life_min, &life_max,
                          &radius_min, &radius_max);

    int to_spawn = result->particle_count;
    if (to_spawn > MAX_PARTICLES)
        to_spawn = MAX_PARTICLES;

    int spawned = 0;
    for (int i = 0; i < MAX_PARTICLES && spawned < to_spawn; i++)
    {
        Particle *p = &ps->particles[i];
        if (p->active)
            continue;

        float angle = rand_range(0.0f, 2.0f * PI);
        float speed = rand_range(speed_min, speed_max);

        p->pos = origin;
        p->vel.x = cosf(angle) * speed;
        p->vel.y = sinf(angle) * speed;
        p->max_life = rand_range(life_min, life_max);
        p->life = p->max_life;
        p->radius = rand_range(radius_min, radius_max);
        p->color = result->result_color;
        p->active = 1;

        spawned++;
    }

    // count tracks the highest occupied slot so update/draw don't have to
    // scan the full MAX_PARTICLES array every frame once the system is sparse
    if (spawned > 0)
    {
        int highest = 0;
        for (int i = 0; i < MAX_PARTICLES; i++)
            if (ps->particles[i].active)
                highest = i + 1;
        if (highest > ps->count)
            ps->count = highest;
    }
}

void particles_update(ParticleSystem *ps, float dt)
{
    if (!ps)
        return;

    // mild drag + gentle "settle" pull toward the ground for fizz/precipitate
    // feel; explosions barely notice it over their short lifetime
    const float drag = 0.98f;

    int highest = 0;
    for (int i = 0; i < ps->count; i++)
    {
        Particle *p = &ps->particles[i];
        if (!p->active)
            continue;

        p->life -= dt;
        if (p->life <= 0.0f)
        {
            p->active = 0;
            continue;
        }

        p->vel.x *= drag;
        p->vel.y *= drag;
        p->pos.x += p->vel.x * dt;
        p->pos.y += p->vel.y * dt;

        // fade alpha as life runs out
        float t = p->life / p->max_life;
        p->color.a = (unsigned char)(255.0f * t);

        highest = i + 1;
    }
    ps->count = highest;
}

void particles_draw(const ParticleSystem *ps)
{
    if (!ps)
        return;

    for (int i = 0; i < ps->count; i++)
    {
        const Particle *p = &ps->particles[i];
        if (!p->active)
            continue;

        DrawCircleV(p->pos, p->radius, p->color);
    }
}

void particles_clear(ParticleSystem *ps)
{
    if (!ps)
        return;

    for (int i = 0; i < MAX_PARTICLES; i++)
        ps->particles[i].active = 0;
    ps->count = 0;
}