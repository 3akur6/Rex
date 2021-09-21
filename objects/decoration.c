#include "horizon.c"
#include "cloud.c"

void rex_game_generate_random_decoration(void)
{
    unsigned char i;
    /* the last one is preserved for trex */
    for (i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT - 1; i++)
    {
        if (rex_objects[i].active == INACTIVE)
            break; /* find inactive object */
    }

    /* all is active (may be unnecessary) */
    if (i == REX_GAME_MAX_OBJECT_AMOUNT)
        return;

    struct rex_game_object *decoration;
    decoration = &rex_objects[i]; /* decoration points to inactive object */
    decoration->active = ACTIVE;
    decoration->type = REX_GAME_OBJECT_DECORATION;

    decoration->x = glfw.width;

    /* get random decoration */
    srand(rex_random_seed + rex_frame);
    enum rex_game_decoration_type decoration_type = rand() % REX_GAME_DECORATION_TYPE_AMOUNT;

    switch (decoration_type)
    {
    case REX_GAME_DECORATION_CLOUD:
    default:
    { /* draw cloud */
        // srand(rex_random_seed + rex_frame);

        struct rex_image image = rex_image_load(IMAGE_CLOUD_ID);
        decoration->width = image.width;
        decoration->height = image.height;

        int y_factor = rand() % (REX_GAME_CLOUD_MAX_Y_POSITION - REX_GAME_CLOUD_MIN_Y_POSITION) + REX_GAME_CLOUD_MIN_Y_POSITION;
        decoration->y = y_factor;
        decoration->detail.decoration = REX_GAME_DECORATION_CLOUD;
    }
    }

    int delta_frame = (decoration->width + glfw.width) / (rex_game_speed * REX_GAME_CLOUD_SPEED);
    // printf("[decoration] min_frame_gap->%d\n", min_frame_gap);

    // srand(rex_random_seed + rex_frame);
    int rand_factor = rand() % REX_GAME_CREATE_OBJECT_GAP_BETWEEN_MIN_AND_MAX;

    decoration->create_at_frame = (rex_frame + rand_factor) % MAX_FRAME_AMOUNT;

    decoration->destroy_at_frame = (decoration->create_at_frame + delta_frame) % MAX_FRAME_AMOUNT;

    /* update last_create_object_frame */
    rex_last_create_decoration_frame = rex_frame;
}

void rex_game_draw_decoration(struct nk_context *ctx, struct rex_game_object *decoration)
{
    /* target destroy frame */
    if (decoration->destroy_at_frame == rex_frame)
    {
        decoration->active = INACTIVE;
        return;
    }

    switch (decoration->detail.decoration)
    {
    case REX_GAME_DECORATION_CLOUD:
        rex_object_cloud_float(ctx, decoration);
        break;
    }
}

void rex_game_draw_freeze_decoration(struct nk_context *ctx, struct rex_game_object *decoration)
{
    switch (decoration->detail.decoration)
    {
    case REX_GAME_DECORATION_CLOUD:
        rex_draw_image(ctx, IMAGE_CLOUD_ID, decoration->x, decoration->y);
        break;
    }
}
