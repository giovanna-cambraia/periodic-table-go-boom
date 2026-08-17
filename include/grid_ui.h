#ifndef GRID_UI_H
#define GRID_UI_H

#include "raylib.h"
#include "elements.h"

typedef enum {
    SELECT_NONE,  // no element locked in yet
    SELECT_A,     // element A locked, choosing B
    SELECT_B      // both locked, ready to react
} SelectionStage;

typedef struct {
    int cursor_period;  
    int cursor_group;    
    const Element *selected_a;
    const Element *selected_b;
    SelectionStage stage;

    Rectangle grid_bounds;
    float tile_size;
} GridUI;

GridUI grid_ui_init(Rectangle grid_bounds);

// moves the cursor by one grid cell in a direction, skipping empty cells;
// dx/dy in {-1,0,1}
void grid_ui_move_cursor(GridUI *ui, int dx, int dy);

// locks in the element under the cursor as A, then B; wraps back to NONE
// (deselecting both) if called a third time
void grid_ui_confirm_selection(GridUI *ui);

void grid_ui_reset_selection(GridUI *ui);

void grid_ui_draw(const GridUI *ui);

#endif