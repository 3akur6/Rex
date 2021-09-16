static unsigned char rex_object_amount = 0;
static unsigned char rex_decoration_amount = 0;
static unsigned char rex_obstacle_amount = 0;
static unsigned char rex_last_create_decoration_frame = 0; /* create decoration at frame last time */
static unsigned char rex_last_create_obstacle_frame = 0;   /* create obstacle at frame last time */
static struct rex_game_object rex_objects[REX_GAME_MAX_OBJECT_AMOUNT];

#include "../objects/trex.c"
#include "../objects/obstacle.c"
#include "../objects/decoration.c"

void rex_debug_print_rex_objects(void)
{
    printf("[rex_debug_print_rex_objects (%d) (%d)]\n", rex_object_amount, rex_frame);

    for (unsigned int i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT; i++)
    {
        struct rex_game_object object = rex_objects[i];
        char active_str[10] = "";
        char type_str[50] = "";
        char detail_str[50] = "";

        switch (object.type)
        {
        case 0:
            continue;
        case REX_GAME_OBJECT_TREX:
            strcpy(type_str, "REX_GAME_OBJECT_TREX");
            switch (object.detail.trex)
            {
            case REX_GAME_TREX_STATIC:
                strcpy(detail_str, "REX_GAME_TREX_STATIC");
                break;
            case REX_GAME_TREX_WALK:
                strcpy(detail_str, "REX_GAME_TREX_WALK");
                break;
            case REX_GAME_TREX_JUMP:
                strcpy(detail_str, "REX_GAME_TREX_JUMP");
                break;
            case REX_GAME_TREX_DUCK:
                strcpy(detail_str, "REX_GAME_TREX_DUCK");
                break;
            }
            break;
        case REX_GAME_OBJECT_OBSTACLE:
            strcpy(type_str, "REX_GAME_OBJECT_OBSTACLE");
            switch (object.detail.obstacle)
            {
            case REX_GAME_OBSTACLE_PTERODACTYL:
                strcpy(detail_str, "REX_GAME_OBSTACLE_PTERODACTYL");
                break;
            case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
                strcpy(detail_str, "REX_GAME_OBSTACLE_CACTUS_SMALL_0");
                break;
            case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
                strcpy(detail_str, "REX_GAME_OBSTACLE_CACTUS_SMALL_1");
                break;
            case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
                strcpy(detail_str, "REX_GAME_OBSTACLE_CACTUS_SMALL_2");
                break;
            case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
                strcpy(detail_str, "REX_GAME_OBSTACLE_CACTUS_LARGE_0");
                break;
            case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
                strcpy(detail_str, "REX_GAME_OBSTACLE_CACTUS_LARGE_1");
                break;
            case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
                strcpy(detail_str, "REX_GAME_OBSTACLE_CACTUS_LARGE_2");
                break;
            }
            break;
        case REX_GAME_OBJECT_DECORATION:
            strcpy(type_str, "REX_GAME_OBJECT_DECORATION");
            switch (object.detail.trex)
            {
            case REX_GAME_DECORATION_CLOUD:
                strcpy(detail_str, "REX_GAME_DECORATION_CLOUD");
                break;
            }
            break;
        }

        if (object.active == nk_true)
            strcpy(active_str, "active");
        else
            strcpy(active_str, "inactive");

        printf(
            "\t%u(%s): type->%s, detail->%s, (x,y)->(%.1f,%.1f), width->%d, height->%d, create_at_frame->%d, destroy_at_frame->%d\n",
            i,
            active_str,
            type_str,
            detail_str,
            object.x, object.y,
            object.width, object.height,
            object.create_at_frame, object.destroy_at_frame);
    }
}

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
    if (duration == REX_GAME_CREATE_OBJECT_MIN_FRAME_GAP && rex_decoration_amount < REX_GAME_MAX_DECORATION_AMOUNT)
        rex_game_generate_random_decoration();

    /* create obstacle object */
    if (rex_frame > rex_last_create_obstacle_frame)
        duration = rex_frame - rex_last_create_obstacle_frame;
    else
        duration = MAX_FRAME_AMOUNT - rex_last_create_obstacle_frame + rex_frame;

    if (duration == REX_GAME_CREATE_OBJECT_MIN_FRAME_GAP && rex_obstacle_amount < REX_GAME_MAX_OBSTACLE_AMOUNT)
        rex_game_generate_random_obstacle();
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

        if (object->active == nk_true)
        {
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
        }
    }
    /* update rex_obstacle_amount */
    rex_object_amount = object_active_amount;
    rex_obstacle_amount = obstacle_active_amount;
    rex_decoration_amount = decoration_active_amount;

    // rex_debug_print_rex_objects();
}
