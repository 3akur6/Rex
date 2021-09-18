void rex_debug_print_rex_object(struct rex_game_object *object)
{
    printf("[rex_debug_print_rex_object] ");
    if (object->type == 0)
    {
        printf("UNINITIALIZED OBJECT\n");
        return;
    }

    char active_str[10] = "";
    char type_str[50] = "";
    char detail_str[50] = "";

    switch (object->type)
    {
    case REX_GAME_OBJECT_TREX:
        strcpy(type_str, "REX_GAME_OBJECT_TREX");
        switch (object->detail.trex)
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
        switch (object->detail.obstacle)
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
        switch (object->detail.trex)
        {
        case REX_GAME_DECORATION_CLOUD:
            strcpy(detail_str, "REX_GAME_DECORATION_CLOUD");
            break;
        }
        break;
    }

    if (object->active == nk_true)
        strcpy(active_str, "active");
    else
        strcpy(active_str, "inactive");

    printf(
        "(%s): type->%s, detail->%s, (x,y)->(%.1f,%.1f), width->%d, height->%d, create_at_frame->%d, destroy_at_frame->%d\n",
        active_str,
        type_str,
        detail_str,
        object->x, object->y,
        object->width, object->height,
        object->create_at_frame, object->destroy_at_frame);
}

void rex_debug_print_rex_objects(void)
{
    printf("[rex_debug_print_rex_objects (%d) (%d) (%d)]\n", rex_object_amount, rex_frame, rex_current_score);

    for (unsigned int i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT; i++)
    { /*  */
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

void rex_debug_print_jump_distance_array(void)
{
    printf("[rex_debug_print_jump_distance_array (%d) (%d)] ", need_frames_amount_one_way, rex_frame);
    for (unsigned int i = 0; i < need_frames_amount_one_way; i++)
        printf("\t%u: %f\n", i, rex_game_trex_jump_distance_array[i]);
}

void rex_debug_print_keyboard_event(void)
{
    printf("[rex_debug_print_keyboard_event (%d) (%d)] ", rex_frame, rex_current_score);

    char key_code[30] = "";
    char key_status[30] = "";

    switch (rex_input_key.code)
    {
    case REX_KEY_CODE_DOWN:
        strcpy(key_code, "REX_KEY_CODE_DOWN");
        break;
    case REX_KEY_CODE_SPACE:
        strcpy(key_code, "REX_KEY_CODE_SPACE");
        break;
    default:
        strcpy(key_code, "REX_KEY_CODE_UNKNOWN");
    }

    switch (rex_input_key.status)
    {
    case REX_KEY_STATUS_REPEAT:
        strcpy(key_status, "REX_KEY_STATUS_REPEAT");
        break;
    case REX_KEY_STATUS_PRESS:
        strcpy(key_status, "REX_KEY_STATUS_PRESS");
        break;
    case REX_KEY_STATUS_RELEASE:
        strcpy(key_status, "REX_KEY_STATUS_RELEASE");
        break;
    default:
        strcpy(key_status, "REX_KEY_STATUS_UNKNOWN");
    }

    printf("code->%s, status->%s\n", key_code, key_status);
}

#include "collision.h"

void collision_debug_print_collision_box(struct collision_box *box, char *msg)
{
    printf("[collision_debug_print_collision_box (%s) (%d)] ", msg, rex_current_score);
    printf("(x,y)->(%f,%f), width->%u, height->%u\n", box->x, box->y, box->width, box->height);
}

void rex_debug_print_rex_collision_collection(struct rex_collision_collection *collection)
{
    unsigned int collection_amount = collection->amount;

    printf("[rex_debug_print_rex_collision_collection (%d) (%d) (%d)]\n", collection_amount, rex_frame, rex_current_score);

    for (unsigned int i = 0; i < collection->amount; i++)
    {
        struct collision_box *box = &collection->boxes[i];

        printf("\t%u: (x,y)->(%f,%f), width->%u, height->%u\n", i, box->x, box->y, box->width, box->height);
    }
}
