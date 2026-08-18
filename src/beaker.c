#include "beaker.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846f
#define SHAKE_DURATION 0.6f
#define FILL_SPEED 3.0f   
#define BUBBLE_COUNT 6 

Beaker beaker_init(Vector2 origin, float width, float height)
{
    Beaker bk;
    bk.origin = origin;
    bk.width = width;
    bk.height = height;

    bk.liquid_color = (Color){180, 200, 255, 255};
    bk.fill_level = 0.0f;
    bk.target_fill = 0.0f;

    bk.bubble_timer = 0.0f;
    bk.shake_timer = 0.0f;
    bk.shake_magnitude = 0.0f;

    bk.active_type = REACT_NONE;
    return bk;
}

void beaker_trigger(Beaker *bk, const ReactionResult *result)
{
    if (!bk || !result)
        return;

    bk->liquid_color = result->result_color;
    bk->active_type = result->type;
    bk->bubble_timer = 0.0f;

    switch (result->type)
    {
    case REACT_NONE:
        bk->target_fill = 0.2f;
        break;
    case REACT_TOXIC_GAS:
        bk->target_fill = 0.35f;
        break;
    default:
        bk->target_fill = 0.35f + result->intensity * 0.5f;
        if (bk->target_fill > 0.92f) bk->target_fill = 0.92f;
        break;
    }

    if (result->type == REACT_EXPLODE)
    {
        bk->shake_timer = SHAKE_DURATION;
        bk->shake_magnitude = 6.0f + result->intensity * 10.0f;
    }
    else
    {
        bk->shake_timer = 0.0f;
        bk->shake_magnitude = 0.0f;
    }
}

void beaker_clear(Beaker *bk)
{
    if (!bk)
        return;
    bk->target_fill = 0.0f;
    bk->active_type = REACT_NONE;
    bk->shake_timer = 0.0f;
    bk->shake_magnitude = 0.0f;
}

void beaker_update(Beaker *bk, float dt)
{
    if (!bk)
        return;

    float diff = bk->target_fill - bk->fill_level;
    bk->fill_level += diff * (1.0f - expf(-FILL_SPEED * dt));
    if (fabsf(diff) < 0.001f)
        bk->fill_level = bk->target_fill;

    bk->bubble_timer += dt;

    if (bk->shake_timer > 0.0f)
    {
        bk->shake_timer -= dt;
        if (bk->shake_timer < 0.0f)
            bk->shake_timer = 0.0f;
    }
}


typedef struct {
    float neck_w, neck_h;
    float body_top_w, body_bottom_w;
    float cx;         
    float body_top_y; 
    float body_bottom_y;
} BeakerGeom;

static BeakerGeom beaker_geom(const Beaker *bk)
{
    BeakerGeom g;
    g.neck_w = bk->width * 0.28f;
    g.neck_h = bk->height * 0.22f;
    g.body_top_w = g.neck_w;
    g.body_bottom_w = bk->width;
    g.cx = bk->width * 0.5f;
    g.body_top_y = g.neck_h;
    g.body_bottom_y = bk->height;
    return g;
}

static float body_width_at_y(const BeakerGeom *g, float y)
{
    if (y <= g->body_top_y) return g->body_top_w;
    if (y >= g->body_bottom_y) return g->body_bottom_w;
    float t = (y - g->body_top_y) / (g->body_bottom_y - g->body_top_y);
    return g->body_top_w + (g->body_bottom_w - g->body_top_w) * t;
}

Vector2 beaker_liquid_point(const Beaker *bk)
{
    Vector2 p = { 0, 0 };
    if (!bk)
        return p;

    BeakerGeom g = beaker_geom(bk);
    float liquid_h = bk->fill_level * (g.body_bottom_y - g.body_top_y);
    float surface_y = g.body_bottom_y - liquid_h;

    p.x = bk->origin.x + g.cx;
    p.y = bk->origin.y + surface_y;
    return p;
}

static Vector2 shake_offset(const Beaker *bk)
{
    Vector2 off = { 0, 0 };
    if (bk->shake_timer <= 0.0f)
        return off;

    float t = bk->shake_timer / SHAKE_DURATION; 
    float amp = bk->shake_magnitude * t;
    off.x = sinf(bk->shake_timer * 60.0f) * amp;
    off.y = cosf(bk->shake_timer * 47.0f) * amp * 0.4f;
    return off;
}

static void draw_quad_fill(float cx, float y_top, float y_bottom,
                            float w_top, float w_bottom, Color color)
{
    Vector2 tl = { cx - w_top / 2.0f, y_top };
    Vector2 tr = { cx + w_top / 2.0f, y_top };
    Vector2 bl = { cx - w_bottom / 2.0f, y_bottom };
    Vector2 br = { cx + w_bottom / 2.0f, y_bottom };

    DrawTriangle(tl, bl, br, color);
    DrawTriangle(tl, br, tr, color);
}

void beaker_draw(const Beaker *bk)
{
    if (!bk)
        return;

    Vector2 off = shake_offset(bk);
    float ox = bk->origin.x + off.x;
    float oy = bk->origin.y + off.y;

    BeakerGeom g = beaker_geom(bk);

    if (bk->fill_level > 0.001f)
    {
        float liquid_h = bk->fill_level * (g.body_bottom_y - g.body_top_y);
        float surface_y = g.body_bottom_y - liquid_h;
        float w_top = body_width_at_y(&g, surface_y);

        draw_quad_fill(ox + g.cx, oy + surface_y, oy + g.body_bottom_y,
                       w_top, g.body_bottom_w, Fade(bk->liquid_color, 0.85f));

        DrawLineEx((Vector2){ ox + g.cx - w_top / 2.0f, oy + surface_y },
                   (Vector2){ ox + g.cx + w_top / 2.0f, oy + surface_y },
                   2.0f, Fade(WHITE, 0.5f));
    }

    if (bk->active_type == REACT_TOXIC_GAS && bk->fill_level > 0.01f)
    {
        float surface_y = g.body_bottom_y - bk->fill_level * (g.body_bottom_y - g.body_top_y);
        for (int i = 0; i < 4; i++)
        {
            float phase = bk->bubble_timer * 0.6f + (float)i * 1.7f;
            float px = ox + g.cx + sinf(phase) * (g.neck_w * 0.5f);
            float py = oy + surface_y - 6.0f - fmodf(bk->bubble_timer * 10.0f + i * 9.0f, 40.0f);
            float alpha = 0.35f * (1.0f - fmodf(bk->bubble_timer * 10.0f + i * 9.0f, 40.0f) / 40.0f);
            DrawCircleV((Vector2){ px, py }, 10.0f + i * 2.0f, Fade(bk->liquid_color, alpha));
        }
    }

    if ((bk->active_type == REACT_FIZZ || bk->active_type == REACT_EXPLODE) &&
        bk->fill_level > 0.01f)
    {
        float surface_y = g.body_bottom_y - bk->fill_level * (g.body_bottom_y - g.body_top_y);
        for (int i = 0; i < BUBBLE_COUNT; i++)
        {
            float speed = 30.0f + (i % 3) * 15.0f;
            float cycle = 0.9f + (i % 4) * 0.15f;
            float t = fmodf(bk->bubble_timer * speed * 0.02f + (float)i / BUBBLE_COUNT, cycle) / cycle;
            float w_here = body_width_at_y(&g, surface_y + t * (g.body_bottom_y - surface_y));
            float bx = ox + g.cx + sinf((float)i * 2.1f) * (w_here * 0.35f);
            float by = oy + g.body_bottom_y - t * (g.body_bottom_y - surface_y);
            float r = 2.0f + 2.0f * (1.0f - t);
            DrawCircleV((Vector2){ bx, by }, r, Fade(WHITE, 0.5f * (1.0f - t)));
        }
    }

    Color glass = Fade((Color){120, 130, 140, 255}, 0.9f);
    float lw = 3.0f;

    float nx0 = ox + g.cx - g.neck_w / 2.0f;
    float nx1 = ox + g.cx + g.neck_w / 2.0f;
    float bx0 = ox + g.cx - g.body_bottom_w / 2.0f;
    float bx1 = ox + g.cx + g.body_bottom_w / 2.0f;

    DrawLineEx((Vector2){ nx0, oy }, (Vector2){ nx0, oy + g.body_top_y }, lw, glass);
    DrawLineEx((Vector2){ nx1, oy }, (Vector2){ nx1, oy + g.body_top_y }, lw, glass);
    DrawLineEx((Vector2){ nx0, oy + g.body_top_y }, (Vector2){ bx0, oy + g.body_bottom_y }, lw, glass);
    DrawLineEx((Vector2){ nx1, oy + g.body_top_y }, (Vector2){ bx1, oy + g.body_bottom_y }, lw, glass);
    DrawLineEx((Vector2){ bx0, oy + g.body_bottom_y }, (Vector2){ bx1, oy + g.body_bottom_y }, lw, glass);
    DrawLineEx((Vector2){ nx0, oy }, (Vector2){ nx1, oy }, lw, glass);

    if (bk->active_type == REACT_EXPLODE && bk->shake_timer > 0.0f)
    {
        float t = bk->shake_timer / SHAKE_DURATION;
        DrawCircleV((Vector2){ ox + g.cx, oy + g.body_bottom_y - (g.body_bottom_y - g.body_top_y) * 0.4f },
                    g.body_bottom_w * 0.7f * (1.0f - t) + 10.0f,
                    Fade(bk->liquid_color, 0.25f * t));
    }
}