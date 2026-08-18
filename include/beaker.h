#ifndef BEAKER_H
#define BEAKER_H

#include "raylib.h"
#include "reaction.h"

typedef struct {
    Vector2 origin;       // top-left of the beaker's bounding box
    float width;
    float height;

    Color liquid_color;
    float fill_level;     // 0.0 (empty) - 1.0 (full), animates toward target
    float target_fill;

    float bubble_timer;   // internal clock driving bubble spawn cadence
    float shake_timer;    // internal clock for explosion screen-shake/wobble
    float shake_magnitude;

    ReactionType active_type; // drives bubble rate / shake / glow behavior
} Beaker;

Beaker beaker_init(Vector2 origin, float width, float height);

// call when a reaction fires; sets liquid color/fill target and kicks off
// type-appropriate animation (bubbling for fizz, shake for explode, etc.)
void beaker_trigger(Beaker *bk, const ReactionResult *result);

// call when selection resets; drains the liquid back to empty
void beaker_clear(Beaker *bk);

void beaker_update(Beaker *bk, float dt);

// returns the on-screen point liquid particles/bubbles should originate from
// (center of the liquid surface) - useful for feeding particles_spawn_burst
Vector2 beaker_liquid_point(const Beaker *bk);

void beaker_draw(const Beaker *bk);

#endif