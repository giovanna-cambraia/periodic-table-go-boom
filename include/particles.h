#ifndef PARTICLES_H
#define PARTICLES_H

#include "raylib.h"
#include "reaction.h"

#define MAX_PARTICLES 512

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float life;       
    float max_life;   
    float radius;
    Color color;
    int active;
} Particle;

typedef struct {
    Particle particles[MAX_PARTICLES];
    int count; 
} ParticleSystem;

ParticleSystem particles_init(void);

void particles_spawn_burst(ParticleSystem *ps, Vector2 origin, const ReactionResult *result);

// advances all active particles by dt, deactivates expired ones
void particles_update(ParticleSystem *ps, float dt);

// draws all active particles (call between BeginDrawing/EndDrawing, 2D context)
void particles_draw(const ParticleSystem *ps);

void particles_clear(ParticleSystem *ps);

#endif