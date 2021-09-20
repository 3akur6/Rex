#include "pterodactyl.c"
#include "cactus.c"

void rex_game_generate_random_obstacle(void)
{
    int min_frame_gap = (int)(glfw.width / (rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED * REX_GAME_MAX_OBSTACLE_AMOUNT)) + 1;

    if (rex_frame - rex_last_create_obstacle_frame < min_frame_gap)
        return;

    /* replace one of the inactive obstacles with new obstacle */
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

    struct rex_game_object obstacle;
    /* activate obstacle */
    obstacle.active = ACTIVE;
    obstacle.type = REX_GAME_OBJECT_OBSTACLE;

    /* get random type */
    srand(rex_random_seed + rex_frame);
    enum rex_game_object_type detail_type = rand() % REX_GAME_OBSTACLE_TYPE_AMOUNT;

    obstacle.detail.obstacle = detail_type;

    obstacle.x = glfw.width;

    switch (detail_type)
    {
    case REX_GAME_OBSTACLE_PTERODACTYL:
    {
        struct rex_image image = rex_image_load(IMAGE_PTERODACTYL_0_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        /* regenerate seed */
        // srand(rex_random_seed + rex_frame);
        /* random level to differentiate the y axis of pterodactyl */
        int level = rand() % 3;
        switch (level)
        {
        case 0:
            obstacle.y = REX_GAME_PTERODACTYL_Y_POSITION_1;
            break;
        case 1:
            obstacle.y = REX_GAME_PTERODACTYL_Y_POSITION_2;
            break;
        case 2:
            obstacle.y = REX_GAME_PTERODACTYL_Y_POSITION_3;
            break;
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
    {
        struct rex_image image = rex_image_load(IMAGE_CACTUS_SMALL_0_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        obstacle.y = REX_GAME_CACTUS_SMALL_Y_POSITION;
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
    {
        struct rex_image image = rex_image_load(IMAGE_CACTUS_SMALL_1_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        obstacle.y = REX_GAME_CACTUS_SMALL_Y_POSITION;
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
    {
        struct rex_image image = rex_image_load(IMAGE_CACTUS_SMALL_2_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        obstacle.y = REX_GAME_CACTUS_SMALL_Y_POSITION;
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
    {
        struct rex_image image = rex_image_load(IMAGE_CACTUS_LARGE_0_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        obstacle.y = REX_GAME_CACTUS_LARGE_Y_POSITION;
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
    {
        struct rex_image image = rex_image_load(IMAGE_CACTUS_LARGE_1_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        obstacle.y = REX_GAME_CACTUS_LARGE_Y_POSITION;
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
    {
        struct rex_image image = rex_image_load(IMAGE_CACTUS_LARGE_2_ID);
        obstacle.width = image.width;
        obstacle.height = image.height;
        obstacle.y = REX_GAME_CACTUS_LARGE_Y_POSITION;
        break;
    }
    }

    int delta_frame = (obstacle.width + glfw.width) / (rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED);
    printf("[obstacle] min_frame_gap->%d\n", min_frame_gap);

    // srand(rex_random_seed + rex_frame);
    int rand_factor = rand() % REX_GAME_CREATE_OBJECT_GAP_BETWEEN_MIN_AND_MAX;

    obstacle.create_at_frame = rex_frame + rand_factor + min_frame_gap;
    obstacle.destroy_at_frame = obstacle.create_at_frame + delta_frame;

    /* save object */
    rex_objects[i] = obstacle;

    /* update last_create_object_frame */
    rex_last_create_obstacle_frame = obstacle.create_at_frame;
}

void rex_game_draw_obstacle(struct nk_context *ctx, struct rex_game_object *obstacle)
{
    /* target destroy frame */
    if (rex_frame == obstacle->destroy_at_frame)
    {
        obstacle->active = INACTIVE;
        return;
    }

    float current_x = obstacle->x;
    float current_y = obstacle->y;

    switch (obstacle->detail.obstacle)
    {
    case REX_GAME_OBSTACLE_PTERODACTYL:
        rex_object_pterodactyl_fly(ctx, obstacle);
        break;
    case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
    case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
    case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
    case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
    case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
    case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
        rex_object_cactus_move(ctx, obstacle);
        break;
    }
}

struct rex_game_object *rex_game_get_closest_obstacle(void)
{
    struct rex_game_object *need_object; /* result */
    struct rex_game_object *object;
    float min = 0; /* default */

    struct rex_game_object *trex = rex_object_get_trex(); /* get trex object */
    float trex_x = trex->x;
    float trex_x_right = trex->x + trex->width;

    for (unsigned char i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT - 1; i++)
    {
        object = &rex_objects[i];
        float object_x = object->x;
        float object_x_right = object_x + object->width;
        if (object->active == ACTIVE && object->type == REX_GAME_OBJECT_OBSTACLE && trex_x < object_x_right)
        {
            float delta_x = object_x - trex_x_right;
            if (delta_x < min || min == 0)
            {
                need_object = object; /* need_object points to current obstacle */
                min = delta_x;
            }
        }
    }

    return need_object;
}

void rex_game_draw_freeze_obstacle(struct nk_context *ctx, struct rex_game_object *obstacle)
{
    int image_id = -1; /* invalid id */
    switch (obstacle->detail.obstacle)
    {
    case REX_GAME_OBSTACLE_PTERODACTYL:
        image_id = IMAGE_PTERODACTYL_0_ID;
        break;
    case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
        image_id = IMAGE_CACTUS_SMALL_0_ID;
        break;
    case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
        image_id = IMAGE_CACTUS_SMALL_1_ID;
        break;
    case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
        image_id = IMAGE_CACTUS_SMALL_2_ID;
        break;
    case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
        image_id = IMAGE_CACTUS_LARGE_0_ID;
        break;
    case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
        image_id = IMAGE_CACTUS_LARGE_1_ID;
        break;
    case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
        image_id = IMAGE_CACTUS_LARGE_2_ID;
        break;
    }
    if (image_id != -1)
        rex_draw_image(ctx, image_id, obstacle->x, obstacle->y);
}
