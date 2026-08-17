#ifndef REACTION_H
#define REACTION_H

#include "elements.h"
#include "raylib.h"

typedef enum {
    REACT_NONE,          // inert / no meaningful reaction
    REACT_COLOR_CHANGE,  // mild, e.g. covalent bond, gentle oxidation
    REACT_FIZZ,          // bubbling / effervescence
    REACT_PRECIPITATE,   // ionic solid forms, color shift + settle
    REACT_TOXIC_GAS,     // hazardous gas byproduct
    REACT_EXPLODE        // violent, high-energy reaction
} ReactionType;

typedef struct {
    ReactionType type;
    float intensity;       
    Color result_color;    
    int particle_count;    
    const char *description; 
} ReactionResult;

// pure, deterministic classification from family + electronegativity difference.
// same pair of elements always returns the same ReactionType.
ReactionType reaction_classify(const Element *a, const Element *b);

// wraps reaction_classify() and rolls randomness into intensity/color/particles.
// call srand() once at program start 
ReactionResult reaction_compute(const Element *a, const Element *b);

const char *reaction_type_description(ReactionType type);

#endif