static unsigned char rex_object_amount = 0;
static unsigned char rex_obstacle_amount = 0;
static struct rex_game_object rex_objects[REX_GAME_MAX_OBJECT_AMOUNT];

#include "../objects/trex.c"
#include "../objects/obstacle.c"
#include "../objects/decoration.c"

void rex_debug_print_rex_objects(void)
{
    printf("[rex_debug_print_rex_obstacles (%d)]\n", rex_object_amount);
    for (unsigned int i = 0; i < rex_object_amount; i++)
    {
        struct rex_game_object object = rex_objects[i];
        printf(
            "\t%u: type->%d, (x,y)->(%f,%f), width->%d, height->%d, create_at_frame->%d, destroy_at_frame->%d\n",
            i,
            object.type,
            object.x, object.y,
            object.width, object.height,
            object.create_at_frame, object.destroy_at_frame);
    }
}

void rex_game_draw_objects(struct nk_context *ctx)
{
    /* count the number of active objects then update rex_object_amount */
    unsigned int object_active_amount = 0;

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
                rex_game_draw_obstacle(ctx, object);
                break;
            case REX_GAME_OBJECT_DECORATION:
                rex_game_draw_decoration(ctx, object);
                break;
            }
        }
    }
    /* update rex_obstacle_amount */
    rex_object_amount = object_active_amount;

    // rex_debug_print_rex_objects();
}
