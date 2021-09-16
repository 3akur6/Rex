void rex_object_cactus_move(struct nk_context *ctx, struct rex_game_object *cactus)
{
    int image_id = 0;
    switch (cactus->detail.obstacle)
    {
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

    if (cactus->create_at_frame < cactus->destroy_at_frame)
    { /* create_at_frame < destroy_at_frame */
        if (rex_frame >= cactus->create_at_frame && rex_frame < cactus->destroy_at_frame)
        {
            /* draw cactus. Update (x, y) will be done out of switch for all cactuss */
            rex_draw_image(ctx, image_id, cactus->x, cactus->y);
            /* update (x, y) here */
            cactus->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
        }
    }
    else
    { /* create_at_frame > destroy_at_frame */
        if (rex_frame >= cactus->create_at_frame || rex_frame < cactus->destroy_at_frame)
        {
            rex_draw_image(ctx, image_id, cactus->x, cactus->y);
            /* update (x, y) here */
            cactus->x -= rex_game_speed * REX_GAME_OBJECT_MOVE_SPEED;
        }
    }
}
