#include "elements.h"
#include <string.h>

const Element PERIODIC_TABLE[ELEMENT_COUNT] = {
    {"H", "Hydrogen", 1, 1, 1, FAM_NONMETAL, 2.20f, 1, {255, 255, 255, 255}},
    {"He", "Helium", 2, 1, 18, FAM_NOBLE_GAS, 0.0f, 2, {217, 255, 255, 255}},
    {"Li", "Lithium", 3, 2, 1, FAM_ALKALI, 0.98f, 1, {204, 128, 255, 255}},
    {"Be", "Beryllium", 4, 2, 2, FAM_ALKALINE_EARTH, 1.57f, 2, {194, 255, 0, 255}},
    {"B", "Boron", 5, 2, 13, FAM_METALLOID, 2.04f, 3, {255, 181, 181, 255}},
    {"C", "Carbon", 6, 2, 14, FAM_NONMETAL, 2.55f, 4, {144, 144, 144, 255}},
    {"N", "Nitrogen", 7, 2, 15, FAM_NONMETAL, 3.04f, 5, {48, 80, 248, 255}},
    {"O", "Oxygen", 8, 2, 16, FAM_NONMETAL, 3.44f, 6, {255, 13, 13, 255}},
    {"F", "Fluorine", 9, 2, 17, FAM_HALOGEN, 3.98f, 7, {144, 224, 80, 255}},
    {"Ne", "Neon", 10, 2, 18, FAM_NOBLE_GAS, 0.0f, 8, {179, 227, 245, 255}},
    {"Na", "Sodium", 11, 3, 1, FAM_ALKALI, 0.93f, 1, {171, 92, 242, 255}},
    {"Mg", "Magnesium", 12, 3, 2, FAM_ALKALINE_EARTH, 1.31f, 2, {138, 255, 0, 255}},
    {"Al", "Aluminium", 13, 3, 13, FAM_POST_TRANSITION, 1.61f, 3, {191, 166, 166, 255}},
    {"Si", "Silicon", 14, 3, 14, FAM_METALLOID, 1.90f, 4, {240, 200, 160, 255}},
    {"P", "Phosphorus", 15, 3, 15, FAM_NONMETAL, 2.19f, 5, {255, 128, 0, 255}},
    {"S", "Sulfur", 16, 3, 16, FAM_NONMETAL, 2.58f, 6, {255, 255, 48, 255}},
    {"Cl", "Chlorine", 17, 3, 17, FAM_HALOGEN, 3.16f, 7, {31, 240, 31, 255}},
    {"Ar", "Argon", 18, 3, 18, FAM_NOBLE_GAS, 0.0f, 8, {128, 209, 227, 255}},
    {"K", "Potassium", 19, 4, 1, FAM_ALKALI, 0.82f, 1, {143, 64, 212, 255}},
    {"Ca", "Calcium", 20, 4, 2, FAM_ALKALINE_EARTH, 1.00f, 2, {61, 255, 0, 255}},
    {"Sc", "Scandium", 21, 4, 3, FAM_TRANSITION, 1.36f, 2, {230, 230, 230, 255}},
    {"Ti", "Titanium", 22, 4, 4, FAM_TRANSITION, 1.54f, 2, {191, 194, 199, 255}},
    {"V", "Vanadium", 23, 4, 5, FAM_TRANSITION, 1.63f, 2, {166, 166, 171, 255}},
    {"Cr", "Chromium", 24, 4, 6, FAM_TRANSITION, 1.66f, 1, {138, 153, 199, 255}},
    {"Mn", "Manganese", 25, 4, 7, FAM_TRANSITION, 1.55f, 2, {156, 122, 199, 255}},
    {"Fe", "Iron", 26, 4, 8, FAM_TRANSITION, 1.83f, 2, {224, 102, 51, 255}},
    {"Co", "Cobalt", 27, 4, 9, FAM_TRANSITION, 1.88f, 2, {240, 144, 160, 255}},
    {"Ni", "Nickel", 28, 4, 10, FAM_TRANSITION, 1.91f, 2, {80, 208, 80, 255}},
    {"Cu", "Copper", 29, 4, 11, FAM_TRANSITION, 1.90f, 1, {200, 128, 51, 255}},
    {"Zn", "Zinc", 30, 4, 12, FAM_TRANSITION, 1.65f, 2, {125, 128, 176, 255}},
    {"Ga", "Gallium", 31, 4, 13, FAM_POST_TRANSITION, 1.81f, 3, {194, 143, 143, 255}},
    {"Ge", "Germanium", 32, 4, 14, FAM_METALLOID, 2.01f, 4, {102, 143, 143, 255}},
    {"As", "Arsenic", 33, 4, 15, FAM_METALLOID, 2.18f, 5, {189, 128, 227, 255}},
    {"Se", "Selenium", 34, 4, 16, FAM_NONMETAL, 2.55f, 6, {255, 161, 0, 255}},
    {"Br", "Bromine", 35, 4, 17, FAM_HALOGEN, 2.96f, 7, {166, 41, 41, 255}},
    {"Kr", "Krypton", 36, 4, 18, FAM_NOBLE_GAS, 3.00f, 8, {92, 184, 209, 255}},
    {"Rb", "Rubidium", 37, 5, 1, FAM_ALKALI, 0.82f, 1, {112, 46, 176, 255}},
    {"Sr", "Strontium", 38, 5, 2, FAM_ALKALINE_EARTH, 0.95f, 2, {0, 255, 0, 255}},
    {"Y", "Yttrium", 39, 5, 3, FAM_TRANSITION, 1.22f, 2, {148, 255, 255, 255}},
    {"Zr", "Zirconium", 40, 5, 4, FAM_TRANSITION, 1.33f, 2, {148, 224, 224, 255}},
    {"Nb", "Niobium", 41, 5, 5, FAM_TRANSITION, 1.60f, 1, {115, 194, 201, 255}},
    {"Mo", "Molybdenum", 42, 5, 6, FAM_TRANSITION, 2.16f, 1, {84, 181, 181, 255}},
    {"Tc", "Technetium", 43, 5, 7, FAM_TRANSITION, 1.90f, 2, {59, 158, 158, 255}},
    {"Ru", "Ruthenium", 44, 5, 8, FAM_TRANSITION, 2.20f, 1, {36, 143, 143, 255}},
    {"Rh", "Rhodium", 45, 5, 9, FAM_TRANSITION, 2.28f, 1, {10, 125, 140, 255}},
    {"Pd", "Palladium", 46, 5, 10, FAM_TRANSITION, 2.20f, 18, {0, 105, 133, 255}},
    {"Ag", "Silver", 47, 5, 11, FAM_TRANSITION, 1.93f, 1, {192, 192, 192, 255}},
    {"Cd", "Cadmium", 48, 5, 12, FAM_TRANSITION, 1.69f, 2, {255, 217, 143, 255}},
    {"In", "Indium", 49, 5, 13, FAM_POST_TRANSITION, 1.78f, 3, {166, 117, 115, 255}},
    {"Sn", "Tin", 50, 5, 14, FAM_POST_TRANSITION, 1.96f, 4, {102, 128, 128, 255}},
    {"Sb", "Antimony", 51, 5, 15, FAM_METALLOID, 2.05f, 5, {158, 99, 181, 255}},
    {"Te", "Tellurium", 52, 5, 16, FAM_METALLOID, 2.10f, 6, {212, 122, 0, 255}},
    {"I", "Iodine", 53, 5, 17, FAM_HALOGEN, 2.66f, 7, {148, 0, 148, 255}},
    {"Xe", "Xenon", 54, 5, 18, FAM_NOBLE_GAS, 2.60f, 8, {66, 158, 176, 255}},
    {"Cs", "Cesium", 55, 6, 1, FAM_ALKALI, 0.79f, 1, {87, 23, 143, 255}},
    {"Ba", "Barium", 56, 6, 2, FAM_ALKALINE_EARTH, 0.89f, 2, {0, 201, 0, 255}},
    {"La", "Lanthanum", 57, 8, 3, FAM_LANTHANIDE, 1.10f, 2, {112, 212, 255, 255}},
    {"Ce", "Cerium", 58, 8, 4, FAM_LANTHANIDE, 1.12f, 2, {255, 255, 199, 255}},
    {"Pr", "Praseodymium", 59, 8, 5, FAM_LANTHANIDE, 1.13f, 2, {217, 255, 199, 255}},
    {"Nd", "Neodymium", 60, 8, 6, FAM_LANTHANIDE, 1.14f, 2, {199, 255, 199, 255}},
    {"Pm", "Promethium", 61, 8, 7, FAM_LANTHANIDE, 1.13f, 2, {163, 255, 199, 255}},
    {"Sm", "Samarium", 62, 8, 8, FAM_LANTHANIDE, 1.17f, 2, {143, 255, 199, 255}},
    {"Eu", "Europium", 63, 8, 9, FAM_LANTHANIDE, 1.20f, 2, {97, 255, 199, 255}},
    {"Gd", "Gadolinium", 64, 8, 10, FAM_LANTHANIDE, 1.20f, 2, {69, 255, 199, 255}},
    {"Tb", "Terbium", 65, 8, 11, FAM_LANTHANIDE, 1.10f, 2, {48, 255, 199, 255}},
    {"Dy", "Dysprosium", 66, 8, 12, FAM_LANTHANIDE, 1.22f, 2, {31, 255, 199, 255}},
    {"Ho", "Holmium", 67, 8, 13, FAM_LANTHANIDE, 1.23f, 2, {0, 255, 156, 255}},
    {"Er", "Erbium", 68, 8, 14, FAM_LANTHANIDE, 1.24f, 2, {0, 230, 117, 255}},
    {"Tm", "Thulium", 69, 8, 15, FAM_LANTHANIDE, 1.25f, 2, {0, 212, 82, 255}},
    {"Yb", "Ytterbium", 70, 8, 16, FAM_LANTHANIDE, 1.10f, 2, {0, 191, 56, 255}},
    {"Lu", "Lutetium", 71, 8, 17, FAM_LANTHANIDE, 1.27f, 2, {0, 171, 36, 255}},
    {"Hf", "Hafnium", 72, 6, 4, FAM_TRANSITION, 1.30f, 2, {77, 194, 255, 255}},
    {"Ta", "Tantalum", 73, 6, 5, FAM_TRANSITION, 1.50f, 2, {77, 166, 255, 255}},
    {"W", "Tungsten", 74, 6, 6, FAM_TRANSITION, 2.36f, 2, {33, 148, 214, 255}},
    {"Re", "Rhenium", 75, 6, 7, FAM_TRANSITION, 1.90f, 2, {38, 125, 171, 255}},
    {"Os", "Osmium", 76, 6, 8, FAM_TRANSITION, 2.20f, 2, {38, 102, 150, 255}},
    {"Ir", "Iridium", 77, 6, 9, FAM_TRANSITION, 2.20f, 2, {23, 84, 135, 255}},
    {"Pt", "Platinum", 78, 6, 10, FAM_TRANSITION, 2.28f, 1, {208, 208, 224, 255}},
    {"Au", "Gold", 79, 6, 11, FAM_TRANSITION, 2.54f, 1, {255, 209, 35, 255}},
    {"Hg", "Mercury", 80, 6, 12, FAM_TRANSITION, 2.00f, 2, {184, 184, 208, 255}},
    {"Tl", "Thallium", 81, 6, 13, FAM_POST_TRANSITION, 1.62f, 3, {166, 84, 77, 255}},
    {"Pb", "Lead", 82, 6, 14, FAM_POST_TRANSITION, 1.87f, 4, {87, 89, 97, 255}},
    {"Bi", "Bismuth", 83, 6, 15, FAM_POST_TRANSITION, 2.02f, 5, {158, 79, 181, 255}},
    {"Po", "Polonium", 84, 6, 16, FAM_POST_TRANSITION, 2.00f, 6, {171, 92, 0, 255}},
    {"At", "Astatine", 85, 6, 17, FAM_HALOGEN, 2.20f, 7, {117, 79, 69, 255}},
    {"Rn", "Radon", 86, 6, 18, FAM_NOBLE_GAS, 2.20f, 8, {66, 130, 150, 255}},
    {"Fr", "Francium", 87, 7, 1, FAM_ALKALI, 0.79f, 1, {66, 0, 102, 255}},
    {"Ra", "Radium", 88, 7, 2, FAM_ALKALINE_EARTH, 0.90f, 2, {0, 125, 0, 255}},
    {"Ac", "Actinium", 89, 9, 3, FAM_ACTINIDE, 1.10f, 2, {112, 171, 250, 255}},
    {"Th", "Thorium", 90, 9, 4, FAM_ACTINIDE, 1.30f, 2, {0, 186, 255, 255}},
    {"Pa", "Protactinium", 91, 9, 5, FAM_ACTINIDE, 1.50f, 2, {0, 161, 255, 255}},
    {"U", "Uranium", 92, 9, 6, FAM_ACTINIDE, 1.38f, 2, {0, 143, 255, 255}},
    {"Np", "Neptunium", 93, 9, 7, FAM_ACTINIDE, 1.36f, 2, {0, 128, 255, 255}},
    {"Pu", "Plutonium", 94, 9, 8, FAM_ACTINIDE, 1.28f, 2, {0, 107, 255, 255}},
    {"Am", "Americium", 95, 9, 9, FAM_ACTINIDE, 1.13f, 2, {84, 92, 242, 255}},
    {"Cm", "Curium", 96, 9, 10, FAM_ACTINIDE, 1.28f, 2, {120, 92, 227, 255}},
    {"Bk", "Berkelium", 97, 9, 11, FAM_ACTINIDE, 1.30f, 2, {138, 79, 227, 255}},
    {"Cf", "Californium", 98, 9, 12, FAM_ACTINIDE, 1.30f, 2, {161, 54, 212, 255}},
    {"Es", "Einsteinium", 99, 9, 13, FAM_ACTINIDE, 1.30f, 2, {179, 31, 212, 255}},
    {"Fm", "Fermium", 100, 9, 14, FAM_ACTINIDE, 1.30f, 2, {179, 31, 186, 255}},
    {"Md", "Mendelevium", 101, 9, 15, FAM_ACTINIDE, 1.30f, 2, {179, 13, 166, 255}},
    {"No", "Nobelium", 102, 9, 16, FAM_ACTINIDE, 1.30f, 2, {189, 13, 135, 255}},
    {"Lr", "Lawrencium", 103, 9, 17, FAM_ACTINIDE, 1.30f, 3, {199, 0, 102, 255}},
    {"Rf", "Rutherfordium", 104, 7, 4, FAM_TRANSITION, 0.0f, 2, {204, 0, 89, 255}},
    {"Db", "Dubnium", 105, 7, 5, FAM_TRANSITION, 0.0f, 2, {209, 0, 79, 255}},
    {"Sg", "Seaborgium", 106, 7, 6, FAM_TRANSITION, 0.0f, 2, {217, 0, 69, 255}},
    {"Bh", "Bohrium", 107, 7, 7, FAM_TRANSITION, 0.0f, 2, {224, 0, 56, 255}},
    {"Hs", "Hassium", 108, 7, 8, FAM_TRANSITION, 0.0f, 2, {230, 0, 46, 255}},
    {"Mt", "Meitnerium", 109, 7, 9, FAM_TRANSITION, 0.0f, 2, {235, 0, 38, 255}},
    {"Ds", "Darmstadtium", 110, 7, 10, FAM_TRANSITION, 0.0f, 2, {153, 153, 153, 255}},
    {"Rg", "Roentgenium", 111, 7, 11, FAM_TRANSITION, 0.0f, 2, {153, 153, 153, 255}},
    {"Cn", "Copernicium", 112, 7, 12, FAM_TRANSITION, 0.0f, 2, {153, 153, 153, 255}},
    {"Nh", "Nihonium", 113, 7, 13, FAM_TRANSITION, 0.0f, 3, {153, 153, 153, 255}},
    {"Fl", "Flerovium", 114, 7, 14, FAM_POST_TRANSITION, 0.0f, 4, {153, 153, 153, 255}},
    {"Mc", "Moscovium", 115, 7, 15, FAM_TRANSITION, 0.0f, 5, {153, 153, 153, 255}},
    {"Lv", "Livermorium", 116, 7, 16, FAM_TRANSITION, 0.0f, 6, {153, 153, 153, 255}},
    {"Ts", "Tennessine", 117, 7, 17, FAM_HALOGEN, 0.0f, 7, {153, 153, 153, 255}},
    {"Og", "Oganesson", 118, 7, 18, FAM_TRANSITION, 0.0f, 8, {153, 153, 153, 255}},
};

const Element *element_get(int atomic_number)
{
    if (atomic_number < 1 || atomic_number > ELEMENT_COUNT)
        return NULL;
    return &PERIODIC_TABLE[atomic_number - 1];
}

const Element *element_get_by_symbol(const char *symbol)
{
    if (!symbol)
        return NULL;
    for (int i = 0; i < ELEMENT_COUNT; i++)
    {
        if (strcmp(PERIODIC_TABLE[i].symbol, symbol) == 0)
            return &PERIODIC_TABLE[i];
    }
    return NULL;
}

Color family_color(Family f)
{
    switch (f)
    {
    case FAM_ALKALI:
        return (Color){204, 128, 255, 255};
    case FAM_ALKALINE_EARTH:
        return (Color){255, 222, 173, 255};
    case FAM_TRANSITION:
        return (Color){255, 192, 128, 255};
    case FAM_METALLOID:
        return (Color){153, 204, 128, 255};
    case FAM_NONMETAL:
        return (Color){166, 255, 166, 255};
    case FAM_HALOGEN:
        return (Color){255, 255, 128, 255};
    case FAM_NOBLE_GAS:
        return (Color){192, 255, 255, 255};
    case FAM_LANTHANIDE:
        return (Color){255, 191, 255, 255};
    case FAM_ACTINIDE:
        return (Color){255, 153, 204, 255};
    case FAM_POST_TRANSITION:
        return (Color){170, 170, 187, 255};
    default:
        return GRAY;
    }
}

const char *family_name(Family f)
{
    switch (f)
    {
    case FAM_ALKALI:
        return "Alkali Metal";
    case FAM_ALKALINE_EARTH:
        return "Alkaline Earth Metal";
    case FAM_TRANSITION:
        return "Transition Metal";
    case FAM_METALLOID:
        return "Metalloid";
    case FAM_NONMETAL:
        return "Nonmetal";
    case FAM_HALOGEN:
        return "Halogen";
    case FAM_NOBLE_GAS:
        return "Noble Gas";
    case FAM_LANTHANIDE:
        return "Lanthanide";
    case FAM_ACTINIDE:
        return "Actinide";
    case FAM_POST_TRANSITION:
        return "Post-Transition Metal";
    default:
        return "Unknown";
    }
}