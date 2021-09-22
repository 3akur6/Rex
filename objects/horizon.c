#include "objects.h"

struct rex_game_object_horizon
{
    enum rex_game_object_status_type active;
    float x;
    float y;
    unsigned int width;
    unsigned int height;
    float cut_begin; /* cut off subimage from this offset of full image by width */
};

static struct rex_game_object_horizon rex_horizon;

struct rex_game_object_horizon *rex_object_get_horizon(void)
{
    /* global variable */
    return &rex_horizon;
}

#include "../libs/debug.c"

void rex_object_init_horizon(void)
{
    struct rex_game_object_horizon *horizon = rex_object_get_horizon();

    /* horizon has been already initialized */
    if (horizon->active != INACTIVE)
        return;

    /* init */
    horizon->active = ACTIVE;
    horizon->x = REX_GAME_HORIZON_X_POSITION;
    horizon->y = REX_GAME_HORIZON_Y_POSITION;
    horizon->width = glfw.width;
    horizon->height = IMAGE_HORIZON_HEIGHT;
}

void rex_object_draw_freeze_horizon(struct nk_context *ctx, struct rex_game_object_horizon *horizon)
{
    float cut_begin = horizon->cut_begin;
    float horizon_x = horizon->x;
    float horizon_y = horizon->y;

    /* update window width */
    horizon->width = glfw.width;

    float window_width = horizon->width;
    float split = IMAGE_HORIZON_WIDTH - window_width;

    if (cut_begin <= split)
    { /* |--|cut_begin|---|split|-------------------| */
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, cut_begin, 0, window_width, IMAGE_HORIZON_HEIGHT, horizon_x, horizon_y);
    }
    else
    { /* |-----|split|-----|cut_begin|--------------| */
        float part1_width = IMAGE_HORIZON_WIDTH - cut_begin;
        float part2_width = window_width - part1_width;
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, cut_begin, 0, part1_width, IMAGE_HORIZON_HEIGHT, horizon_x, horizon_y);
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, 0, 0, part2_width, IMAGE_HORIZON_HEIGHT, horizon_x + part1_width, horizon_y);
    }
}

void rex_object_horizon_roll(struct nk_context *ctx, struct rex_game_object_horizon *horizon)
{
    rex_object_draw_freeze_horizon(ctx, horizon);

    /* update cut_begin */
    float before = horizon->cut_begin + rex_game_speed * REX_GAME_HORIZON_LINE_ROLL_SPEED;
    if (before >= IMAGE_HORIZON_WIDTH)
        horizon->cut_begin = before - IMAGE_HORIZON_WIDTH;
    else
        horizon->cut_begin = before;
}

void rex_object_draw_horizon(struct nk_context *ctx)
{
    struct rex_game_object_horizon *horizon = rex_object_get_horizon();

    switch (horizon->active)
    {
    case ACTIVE:
        rex_object_horizon_roll(ctx, horizon);
        break;
    case FREEZE:
        rex_object_draw_freeze_horizon(ctx, horizon);
        break;
    }
}

void rex_object_freeze_horizon(void)
{
    struct rex_game_object_horizon *horizon = rex_object_get_horizon();

    horizon->active = FREEZE;
}
