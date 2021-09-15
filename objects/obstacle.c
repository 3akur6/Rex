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
    enum rex_game_object_type detail = rand() % REX_GAME_OBSTACLE_TYPE_AMOUNT;

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

// void rex_game_generate_random_obstacle(void)
// {
//     if (rex_obstacle_amount >= REX_GAME_MAX_OBSTACLE_AMOUNT)
//         return;

//     struct rex_game_object obstacle;
//     /* activate obstacle */
//     obstacle.active = nk_true;

//     srand((unsigned int)time(NULL));
//     enum rex_game_object_type type = rand() % REX_GAME_OBSTACLE_TYPE_AMOUNT;
//     printf("create obstacle, type: %d\n", type);

//     obstacle.type = type;
//     obstacle.x = glfw.width;

//     // /* pterodactyl obstacle is special, having random y position for each instance */
//     // if (type == REX_GAME_OBSTACLE_PTERODACTYL)
//     // {
//     //     /* regenerate seed */
//     //     srand((unsigned int)time(NULL));
//     //     /* random offset in y axis of pterodactyl */
//     //     int offset = rand() % (REX_GAME_PTERODACTYL_MAX_HEIGHT - REX_GAME_PTERODACTYL_MIN_HEIGHT) + REX_GAME_PTERODACTYL_MIN_HEIGHT;

//     //     obstacle.y = REX_GAME_HORIZON_Y_POSITION - offset;
//     // }
//     // else
//     //     obstacle.y = REX_GAME_OBSTACLE_CACTUS_Y_POSITION;

//     switch (type)
//     {
//     case REX_GAME_OBSTACLE_PTERODACTYL:
//     {
//         /* regenerate seed */
//         srand((unsigned int)time(NULL));
//         /* random level to differentiate the y axis of pterodacty1 */
//         int level = rand() % 3;
//         switch (level)
//         {
//         case 0:
//             obstacle.y = REX_GAME_PTERODACTYL_Y_POSITION_1;
//             break;
//         case 1:
//             obstacle.y = REX_GAME_PTERODACTYL_Y_POSITION_2;
//             break;
//         case 2:
//             obstacle.y = REX_GAME_PTERODACTYL_Y_POSITION_3;
//             break;
//         }
//     }
//     case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
//     case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
//     case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
//     {
//         obstacle.y = REX_GAME_CACTUS_SMALL_Y_POSITION;
//         break;
//     }
//     case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
//     case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
//     case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
//     {
//         obstacle.y = REX_GAME_CACTUS_LARGE_Y_POSITION;
//         break;
//     }
//     }

//     srand((unsigned int)time(NULL));
//     unsigned int offset_at_frame = rand() % (REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MAX - REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MIN);

//     obstacle.create_at_frame = rex_frame + offset_at_frame;

//     if (rex_obstacle_amount == 0)
//     {
//         rex_objects[rex_obstacle_amount++] = obstacle;
//         printf("[0: generate] current amount of obstacles: %d\n", rex_obstacle_amount);
//         return;
//     }

//     /* replace the oldest inactive obstacle with new obstacle */
//     unsigned int search_index = (REX_GAME_MAX_OBSTACLE_AMOUNT + rex_obstacle_current_index - 1) % REX_GAME_MAX_OBSTACLE_AMOUNT;
//     struct rex_game_object current = rex_objects[search_index];
//     unsigned int search_times = 0;
//     while (current.active == nk_true && search_times < REX_GAME_MAX_OBSTACLE_AMOUNT)
//     {
//         search_index = (REX_GAME_MAX_OBSTACLE_AMOUNT + rex_obstacle_current_index - 1) % REX_GAME_MAX_OBSTACLE_AMOUNT;
//         current = rex_objects[search_index];
//         search_times++;
//     }

//     printf("[1: generate] current amount of obstacles: %d\n", rex_obstacle_amount);
//     /* all obstacles are active */
//     if (current.active == nk_true)
//         return;

//     /* else find the inactive obstacle which needs to be updated */
//     rex_objects[search_index] = obstacle;
//     rex_obstacle_amount++;
//     printf("[2: generate] current amount of obstacles: %d\n", rex_obstacle_amount);
// }

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

// void rex_game_draw_obstacles(struct nk_context *ctx)
// {
//     /* count the number of active obstacles then update rex_obstacle_amount */
//     unsigned int obstacle_active_amount = 0;

//     struct rex_game_object *obstacle;
//     for (unsigned int i = 0; i < REX_GAME_MAX_OBSTACLE_AMOUNT; i++)
//     {
//         rex_game_get_obstacle(&obstacle);
//         printf("[0: draw] current amount of obstacles: %d\n", rex_obstacle_amount);

//         if (obstacle->active == nk_true)
//         { /* get an active obstacle */
//             obstacle_active_amount++;
//             float current_x = obstacle->x;
//             float current_y = obstacle->y;

//             struct rex_image image;
//             switch (obstacle->type)
//             {
//             case REX_GAME_obstacle_PTERODACTYL:
//             {
//                 /* will get image from cached list */
//                 image = rex_image_load(IMAGE_PTERODACTYL_0_ID);
//                 /* update obstacle width and height */
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     /* object move out of scene */
//                     obstacle->active = nk_false;
//                 else if (rex_frame >= obstacle->create_at_frame)
//                 {
//                     /* draw obstacle. Update (x, y) will be done out of switch for all obstacles */
//                     rex_pterodactyl_fly(ctx, current_x, current_y);
//                     printf("[draw] pterodactyl at (%f, %f)\n", current_x, current_y);
//                 }

//                 break;
//             }
//             case REX_GAME_obstacle_CACTUS_SMALL_0:
//             {
//                 image = rex_image_load(IMAGE_CACTUS_SMALL_0_ID);
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     obstacle->active = nk_false;
//                 else
//                 {
//                     rex_draw_image_since_frame(ctx, IMAGE_CACTUS_SMALL_0_ID, obstacle->create_at_frame, current_x, current_y);
//                     printf("[draw] cactus_small_0 at (%f, %f)\n", current_x, current_y);
//                 }
//                 break;
//             }
//             case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
//             {
//                 image = rex_image_load(IMAGE_CACTUS_SMALL_1_ID);
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     obstacle->active = nk_false;
//                 else
//                 {
//                     rex_draw_image_since_frame(ctx, IMAGE_CACTUS_SMALL_1_ID, obstacle->create_at_frame, current_x, current_y);
//                     printf("[draw] cactus_small_1 at (%f, %f)\n", current_x, current_y);
//                 }
//                 break;
//             }
//             case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
//             {
//                 image = rex_image_load(IMAGE_CACTUS_SMALL_2_ID);
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     obstacle->active = nk_false;
//                 else
//                 {
//                     rex_draw_image_since_frame(ctx, IMAGE_CACTUS_SMALL_2_ID, obstacle->create_at_frame, current_x, current_y);
//                     printf("[draw] cactus_small_2 at (%f, %f)\n", current_x, current_y);
//                 }
//                 break;
//             }
//             case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
//             {
//                 image = rex_image_load(IMAGE_CACTUS_LARGE_0_ID);
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     obstacle->active = nk_false;
//                 else
//                 {
//                     rex_draw_image_since_frame(ctx, IMAGE_CACTUS_LARGE_0_ID, obstacle->create_at_frame, current_x, current_y);
//                     printf("[draw] cactus_large_0 at (%f, %f)\n", current_x, current_y);
//                 }
//                 break;
//             }
//             case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
//             {
//                 image = rex_image_load(IMAGE_CACTUS_LARGE_1_ID);
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     obstacle->active = nk_false;
//                 else
//                 {
//                     rex_draw_image_since_frame(ctx, IMAGE_CACTUS_LARGE_1_ID, obstacle->create_at_frame, current_x, current_y);
//                     printf("[draw] cactus_large_1 at (%f, %f)\n", current_x, current_y);
//                 }
//                 break;
//             }
//             case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
//             {
//                 image = rex_image_load(IMAGE_CACTUS_LARGE_2_ID);
//                 obstacle->width = image.width;
//                 obstacle->height = image.height;

//                 float current_x_right = current_x + obstacle->width;
//                 if (current_x_right < 0)
//                     obstacle->active = nk_false;
//                 else
//                 {
//                     rex_draw_image_since_frame(ctx, IMAGE_CACTUS_LARGE_2_ID, obstacle->create_at_frame, current_x, current_y);
//                     printf("[draw] cactus_large_2 at (%f, %f)\n", current_x, current_y);
//                 }
//                 break;
//             }
//             }
//             /* update (x, y) here */
//             obstacle->x -= rex_game_speed;
//         }
//     }

//     /* update rex_obstacle_amount */
//     rex_obstacle_amount = obstacle_active_amount;
// }