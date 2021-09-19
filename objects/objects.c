static unsigned char rex_object_amount = 0;
static unsigned char rex_decoration_amount = 0;
static unsigned char rex_obstacle_amount = 0;
static unsigned char rex_last_create_decoration_frame = 0; /* create decoration at frame last time */
static unsigned char rex_last_create_obstacle_frame = 0;   /* create obstacle at frame last time */
static struct rex_game_object rex_objects[REX_GAME_MAX_OBJECT_AMOUNT];

#include "../objects/trex.c"
#include "../objects/obstacle.c"
#include "../objects/decoration.c"

void rex_game_generate_random_object(void)
{ /* create a complete object */
    int duration;
    /* create decoration object */
    /* check gap */
    if (rex_frame > rex_last_create_decoration_frame)
        /* |------|last|-------------|rex_frame|----| */
        duration = rex_frame - rex_last_create_decoration_frame;
    else
        /* |-----|rex_frame|--------|last|---------| */
        duration = MAX_FRAME_AMOUNT - rex_last_create_decoration_frame + rex_frame;

    /* shouldn't create new object if duration isn't equal min gap */
    if (duration == (int)(REX_GAME_CREATE_OBJECT_MIN_FRAME_GAP / (0.2 * REX_GAME_OBJECT_MOVE_SPEED)) && rex_decoration_amount < REX_GAME_MAX_DECORATION_AMOUNT)
        rex_game_generate_random_decoration();

    /* create obstacle object */
    if (rex_frame > rex_last_create_obstacle_frame)
        duration = rex_frame - rex_last_create_obstacle_frame;
    else
        duration = MAX_FRAME_AMOUNT - rex_last_create_obstacle_frame + rex_frame;

    if (duration == (int)(REX_GAME_CREATE_OBJECT_MIN_FRAME_GAP / (0.2 * REX_GAME_OBJECT_MOVE_SPEED)) && rex_obstacle_amount < REX_GAME_MAX_OBSTACLE_AMOUNT)
        rex_game_generate_random_obstacle();
}

void rex_game_draw_freeze_object(struct nk_context *ctx, struct rex_game_object *object)
{
    switch (object->type)
    {
    case REX_GAME_OBJECT_TREX:
        rex_draw_image(ctx, IMAGE_TREX_7_ID, object->x, object->y);
        break;
    case REX_GAME_OBJECT_OBSTACLE:
        switch (object->detail.obstacle)
        {
        case REX_GAME_OBSTACLE_PTERODACTYL:
            rex_draw_image(ctx, IMAGE_PTERODACTYL_0_ID, object->x, object->y);
            break;
        case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
            rex_draw_image(ctx, IMAGE_CACTUS_SMALL_0_ID, object->x, object->y);
            break;
        case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
            rex_draw_image(ctx, IMAGE_CACTUS_SMALL_1_ID, object->x, object->y);
            break;
        case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
            rex_draw_image(ctx, IMAGE_CACTUS_SMALL_2_ID, object->x, object->y);
            break;
        case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
            rex_draw_image(ctx, IMAGE_CACTUS_LARGE_0_ID, object->x, object->y);
            break;
        case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
            rex_draw_image(ctx, IMAGE_CACTUS_LARGE_1_ID, object->x, object->y);
            break;
        case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
            rex_draw_image(ctx, IMAGE_CACTUS_LARGE_2_ID, object->x, object->y);
            break;
        }
        break;
    case REX_GAME_OBJECT_DECORATION:
        switch (object->detail.decoration)
        {
        case REX_GAME_DECORATION_CLOUD:
            rex_draw_image(ctx, IMAGE_CLOUD_ID, object->x, object->y);
            break;
        }
        break;
    }
}

void rex_game_draw_objects(struct nk_context *ctx)
{
    /* count the number of active objects then update rex_object_amount */
    unsigned int object_active_amount = 0;
    unsigned int obstacle_active_amount = 0;
    unsigned int decoration_active_amount = 0;

    struct rex_game_object *object;

    for (unsigned int i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT; i++)
    {
        object = &rex_objects[i];

        switch (object->active)
        {
        case ACTIVE:
            object_active_amount++;

            switch (object->type)
            {
            case REX_GAME_OBJECT_TREX:
                rex_game_draw_trex(ctx, object);
                break;
            case REX_GAME_OBJECT_OBSTACLE:
                obstacle_active_amount++;
                rex_game_draw_obstacle(ctx, object);
                break;
            case REX_GAME_OBJECT_DECORATION:
                decoration_active_amount++;
                rex_game_draw_decoration(ctx, object);
                break;
            }
            break;
        case FREEZE:
            rex_game_draw_freeze_object(ctx, object);
            break;
        }
    }
    /* update rex_obstacle_amount */
    rex_object_amount = object_active_amount;
    rex_obstacle_amount = obstacle_active_amount;
    rex_decoration_amount = decoration_active_amount;
}

void rex_game_freeze_objects(void)
{
    struct rex_game_object *object;

    for (unsigned int i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT; i++)
    {
        object = &rex_objects[i];

        if (object->active == ACTIVE)
            object->active = FREEZE; /* set status to freeze */
    }
}
