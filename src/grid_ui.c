#include "grid_ui.h"
#include <stddef.h>
#include <stdio.h>

// elements.h has no period/group lookup, only by symbol/atomic_number,
// so grid_ui does its own scan over PERIODIC_TABLE. Cheap (118 entries,
// only runs on cursor move/confirm, not every frame).
static const Element *element_at_grid(int period, int group)
{
    for (int i = 0; i < ELEMENT_COUNT; i++)
    {
        const Element *e = &PERIODIC_TABLE[i];
        if (e->period == period && e->group == group)
            return e;
    }
    return NULL;
}

GridUI grid_ui_init(Rectangle grid_bounds)
{
    GridUI ui;
    ui.cursor_period = 1;
    ui.cursor_group = 1;
    ui.selected_a = NULL;
    ui.selected_b = NULL;
    ui.stage = SELECT_NONE;
    ui.grid_bounds = grid_bounds;

    // 9 rows (7 periods + lanthanide/actinide strip), 18 columns
    float cell_w = grid_bounds.width / (float)MAX_GROUP;
    float cell_h = grid_bounds.height / 9.0f;
    ui.tile_size = (cell_w < cell_h) ? cell_w : cell_h;

    // H (period 1, group 1) is a real cell, so no need to auto-seek here
    return ui;
}

void grid_ui_move_cursor(GridUI *ui, int dx, int dy)
{
    if (!ui)
        return;
    if (dx == 0 && dy == 0)
        return;

    int period = ui->cursor_period;
    int group = ui->cursor_group;

    for (int step = 0; step < 18; step++)
    {
        int next_period = period + dy;
        int next_group = group + dx;

        if (next_period < 1 || next_period > 9)
            break;
        if (next_group < 1 || next_group > MAX_GROUP)
            break;

        period = next_period;
        group = next_group;

        if (element_at_grid(period, group) != NULL)
        {
            ui->cursor_period = period;
            ui->cursor_group = group;
            return;
        }
    }
}

void grid_ui_confirm_selection(GridUI *ui)
{
    if (!ui)
        return;

    const Element *e = element_at_grid(ui->cursor_period, ui->cursor_group);
    if (!e)
        return; 

    switch (ui->stage)
    {
    case SELECT_NONE:
        ui->selected_a = e;
        ui->stage = SELECT_A;
        break;

    case SELECT_A:
        ui->selected_b = e;
        ui->stage = SELECT_B;
        break;

    case SELECT_B:
        ui->selected_a = NULL;
        ui->selected_b = NULL;
        ui->stage = SELECT_NONE;
        break;
    }
}

void grid_ui_reset_selection(GridUI *ui)
{
    if (!ui)
        return;
    ui->selected_a = NULL;
    ui->selected_b = NULL;
    ui->stage = SELECT_NONE;
}

void grid_ui_draw(const GridUI *ui)
{
    if (!ui)
        return;

    float ox = ui->grid_bounds.x;
    float oy = ui->grid_bounds.y;
    float ts = ui->tile_size;

    for (int i = 0; i < ELEMENT_COUNT; i++)
    {
        const Element *e = &PERIODIC_TABLE[i];
        if (e->period < 1 || e->group < 1)
            continue;

        float x = ox + (float)(e->group - 1) * ts;
        float y = oy + (float)(e->period - 1) * ts;

        Rectangle tile = { x, y, ts - 2.0f, ts - 2.0f };

        Color fill = family_color(e->family);
        DrawRectangleRec(tile, fill);

        if (e == ui->selected_a)
            DrawRectangleLinesEx(tile, 3.0f, GOLD);
        else if (e == ui->selected_b)
            DrawRectangleLinesEx(tile, 3.0f, (Color){0, 200, 255, 255});
        else
            DrawRectangleLinesEx(tile, 1.0f, BLACK);

        DrawText(e->symbol, (int)(x + 4), (int)(y + 4), 10, BLACK);
    }

    float cx = ox + (float)(ui->cursor_group - 1) * ts;
    float cy = oy + (float)(ui->cursor_period - 1) * ts;
    Rectangle cursor_rect = { cx, cy, ts - 2.0f, ts - 2.0f };
    DrawRectangleLinesEx(cursor_rect, 3.0f, RED);

    // hud line: current stage + selections
    char hud[128];
    const Element *cur = element_at_grid(ui->cursor_period, ui->cursor_group);
    switch (ui->stage)
    {
    case SELECT_NONE:
        snprintf(hud, sizeof(hud), "Pick element A: %s",
                 cur ? cur->name : "-");
        break;
    case SELECT_A:
        snprintf(hud, sizeof(hud), "A: %s   |   Pick element B: %s",
                 ui->selected_a->name, cur ? cur->name : "-");
        break;
    case SELECT_B:
        snprintf(hud, sizeof(hud), "A: %s   B: %s   |   Press again to reset",
                 ui->selected_a->name, ui->selected_b->name);
        break;
    }
    DrawText(hud, (int)ox, (int)(oy + ui->grid_bounds.height + 10), 18, BLACK);
}