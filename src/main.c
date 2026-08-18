#include "raylib.h"
#include "elements.h"
#include "reaction.h"
#include "particles.h"
#include "grid_ui.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define SCREEN_W 1000
#define SCREEN_H 720

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "Element Reactor");
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));

    Rectangle grid_bounds = { 20, 20, 900, 450 };
    GridUI ui = grid_ui_init(grid_bounds);

    ParticleSystem ps = particles_init();
    ReactionResult last_result = { REACT_NONE, 0.0f, WHITE, 0, "No reaction yet." };
    int has_reacted = 0;

    Vector2 reaction_point = { SCREEN_W / 2.0f, 600.0f };

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_RIGHT)) grid_ui_move_cursor(&ui, 1, 0);
        if (IsKeyPressed(KEY_LEFT))  grid_ui_move_cursor(&ui, -1, 0);
        if (IsKeyPressed(KEY_DOWN))  grid_ui_move_cursor(&ui, 0, 1);
        if (IsKeyPressed(KEY_UP))    grid_ui_move_cursor(&ui, 0, -1);

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        {
            SelectionStage prev_stage = ui.stage;
            grid_ui_confirm_selection(&ui);

            // stage just transitioned A -> B: both elements are locked in, react
            if (prev_stage == SELECT_A && ui.stage == SELECT_B)
            {
                last_result = reaction_compute(ui.selected_a, ui.selected_b);
                has_reacted = 1;
                particles_spawn_burst(&ps, reaction_point, &last_result);
            }

            // stage just transitioned B -> NONE (third confirm): clear the board
            if (prev_stage == SELECT_B && ui.stage == SELECT_NONE)
            {
                has_reacted = 0;
                particles_clear(&ps);
            }
        }

        if (IsKeyPressed(KEY_R))
        {
            grid_ui_reset_selection(&ui);
            particles_clear(&ps);
            has_reacted = 0;
        }

        particles_update(&ps, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid_ui_draw(&ui);

        // reaction result panel, below the grid + hud line
        int panel_y = 500;
        DrawText("Reaction:", 20, panel_y, 22, DARKGRAY);

        if (has_reacted)
        {
            char line[160];
            snprintf(line, sizeof(line), "%s + %s",
                     ui.selected_a->name, ui.selected_b->name);
            DrawText(line, 20, panel_y + 30, 20, BLACK);
            DrawText(last_result.description, 20, panel_y + 55, 18, DARKGRAY);

            char intensity_line[64];
            snprintf(intensity_line, sizeof(intensity_line), "Intensity: %.2f", last_result.intensity);
            DrawText(intensity_line, 20, panel_y + 80, 16, GRAY);

            DrawCircleV(reaction_point, 18.0f, last_result.result_color);
        }
        else
        {
            DrawText("Pick two elements and press Enter to react.", 20, panel_y + 30, 18, DARKGRAY);
        }

        particles_draw(&ps);

        DrawText("Arrows: move   Enter/Space: select/react   R: reset", 20, SCREEN_H - 30, 16, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}