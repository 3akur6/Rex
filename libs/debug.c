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
