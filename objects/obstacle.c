#include "pterodactyl.c"

void rex_game_generate_random_obstacle(void)
{
    if (rex_obstacle_amount >= REX_GAME_MAX_OBSTACLE_AMOUNT)
        return;

    struct rex_game_object obstacle;
    /* activate obstacle */
    obstacle.active = nk_true;
    obstacle.type = REX_GAME_OBJECT_OBSTACLE;

    /* get random type */
    srand((unsigned int)time(NULL));
    enum rex_game_obstacle_type detail = rand() % REX_GAME_OBSTACLE_TYPE_AMOUNT;

    obstacle.detail.obstacle = detail;
    obstacle.x = glfw.width;

    /* pterodactyl obstacle is special, having random y position for each instance */
    if (detail == REX_GAME_OBSTACLE_PTERODACTYL)
    {
        /* regenerate seed */
        srand((unsigned int)time(NULL));
        /* random offset in y axis of pterodactyl */
        int offset = rand() % (REX_GAME_PTERODACTYL_MAX_HEIGHT - REX_GAME_PTERODACTYL_MIN_HEIGHT) + REX_GAME_PTERODACTYL_MIN_HEIGHT;

        obstacle.y = REX_GAME_HORIZON_Y_POSITION - offset;
    }
    else
        obstacle.y = REX_GAME_OBJECT_CACTUS_Y_POSITION;

    srand((unsigned int)time(NULL));
    unsigned int offset_at_frame = rand() % (REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MAX - REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MIN) + REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MIN;

    obstacle.create_at_frame = (rex_frame + offset_at_frame) % MAX_FRAME_AMOUNT;

    /* replace one of the inactive obstacles with new obstacle */
    for (unsigned int i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT; i++)
    {
        struct rex_game_object current = rex_objects[i];
        if (current.type == REX_GAME_OBJECT_OBSTACLE && current.active == nk_false)
        { /* find an inactive obstacle */
            rex_objects[i] = obstacle;
            rex_object_amount++;
            return;
        }
    }

    /* all obstacles are active */
    return;
}

void rex_game_draw_obstacle(struct nk_context *ctx, struct rex_game_object *obstacle)
{
    float current_x = obstacle->x;
    float current_y = obstacle->y;

    struct rex_image image;
    switch (obstacle->detail.obstacle)
    {
    case REX_GAME_OBSTACLE_PTERODACTYL:
    {
        /* will get image from cached list */
        image = rex_image_load(IMAGE_PTERODACTYL_0_ID);
        /* update obstacle width and height */
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;
        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_pterodactyl_fly(ctx, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_pterodactyl_fly(ctx, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
    {
        image = rex_image_load(IMAGE_CACTUS_SMALL_0_ID);
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;
        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_draw_image(ctx, IMAGE_CACTUS_SMALL_0_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_draw_image(ctx, IMAGE_CACTUS_SMALL_0_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
    {
        image = rex_image_load(IMAGE_CACTUS_SMALL_1_ID);
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;
        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_draw_image(ctx, IMAGE_CACTUS_SMALL_1_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_draw_image(ctx, IMAGE_CACTUS_SMALL_1_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
    {
        image = rex_image_load(IMAGE_CACTUS_SMALL_2_ID);
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;
        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_draw_image(ctx, IMAGE_CACTUS_SMALL_2_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_draw_image(ctx, IMAGE_CACTUS_SMALL_2_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
    {
        image = rex_image_load(IMAGE_CACTUS_LARGE_0_ID);
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;

        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_draw_image(ctx, IMAGE_CACTUS_LARGE_0_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_draw_image(ctx, IMAGE_CACTUS_LARGE_0_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
    {
        image = rex_image_load(IMAGE_CACTUS_LARGE_1_ID);
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;
        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_draw_image(ctx, IMAGE_CACTUS_LARGE_1_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_draw_image(ctx, IMAGE_CACTUS_LARGE_1_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
    {
        image = rex_image_load(IMAGE_CACTUS_LARGE_2_ID);
        obstacle->width = image.width;
        obstacle->height = image.height;

        float current_x_right = current_x + obstacle->width;
        unsigned int need_frames = current_x_right / rex_game_speed;
        obstacle->destroy_at_frame = (rex_frame + need_frames) % MAX_FRAME_AMOUNT;

        if (current_x_right < 0)
            obstacle->active = nk_false;
        /* ugly code */
        if (obstacle->create_at_frame < obstacle->destroy_at_frame)
        { /* create_at_frame < destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame && rex_frame < obstacle->destroy_at_frame)
            {
                /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
                rex_draw_image(ctx, IMAGE_CACTUS_LARGE_2_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        else
        { /* create_at_frame > destroy_at_frame */
            if (rex_frame >= obstacle->create_at_frame || rex_frame < obstacle->destroy_at_frame)
            {
                rex_draw_image(ctx, IMAGE_CACTUS_LARGE_2_ID, current_x, current_y);
                /* update (x, y) here */
                obstacle->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
            }
        }
        break;
    }
    }
}