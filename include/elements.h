#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "raylib.h"

#define ELEMENT_COUNT 118
#define MAX_PERIOD 7
#define MAX_GROUP 18

typedef enum {
    FAM_ALKALI,
    FAM_ALKALINE_EARTH,
    FAM_TRANSITION,
    FAM_METALLOID,
    FAM_NONMETAL,
    FAM_HALOGEN,
    FAM_NOBLE_GAS,
    FAM_LANTHANIDE,
    FAM_ACTINIDE,
    FAM_POST_TRANSITION
} Family;

typedef struct {
    const char *symbol;
    const char *name;
    int atomic_number;
    int period;               // grid row (1-7); lanthanides/actinides use 8-9
    int group;                // grid column (1-18); 0 if not applicable (lanth/actin)
    Family family;
    float electronegativity;  // 0.0f if undefined (noble gases, some actinides)
    int valence_electrons;
    Color base_color;         
} Element;

// full static periodic table, indexed 0..ELEMENT_COUNT-1 (atomic_number - 1)
extern const Element PERIODIC_TABLE[ELEMENT_COUNT];

// lookup by atomic number (1-118), returns NULL if out of range
const Element *element_get(int atomic_number);

// lookup by symbol (e.g. "Na"), returns NULL if not found
const Element *element_get_by_symbol(const char *symbol);

Color family_color(Family f);

const char *family_name(Family f);

#endif