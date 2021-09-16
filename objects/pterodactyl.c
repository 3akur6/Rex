/* avoid calling this function in other part */
void _rex_pterodactyl_fly(struct nk_context *ctx, float x, float y)
{
    if (rex_frame & REX_GAME_PTERODACTYL_REFRESH_SPEED)
        rex_draw_image(ctx, IMAGE_PTERODACTYL_0_ID, x, y);
    else
        rex_draw_image(ctx, IMAGE_PTERODACTYL_1_ID, x, y);

    return;
}

void rex_object_pterodactyl_fly(struct nk_context *ctx, struct rex_game_object *pterodactyl)
{
    if (pterodactyl->create_at_frame < pterodactyl->destroy_at_frame)
    { /* create_at_frame < destroy_at_frame */
        if (rex_frame >= pterodactyl->create_at_frame && rex_frame < pterodactyl->destroy_at_frame)
        {
            /* draw pterodactyl. Update (x, y) will be done out of switch for all pterodactyls */
            _rex_pterodactyl_fly(ctx, pterodactyl->x, pterodactyl->y);
            /* update (x, y) here */
            pterodactyl->x -= rex_game_speed * REX_GAME_PTERODACTYL_SPEED;
        }
    }
    else
    { /* create_at_frame > destroy_at_frame */
        if (rex_frame >= pterodactyl->create_at_frame || rex_frame < pterodactyl->destroy_at_frame)
        {
            _rex_pterodactyl_fly(ctx, pterodactyl->x, pterodactyl->y);
            /* update (x, y) here */
            pterodactyl->x -= rex_game_speed * REX_GAME_PTERODACTYL_SPEED;
        }
    }
}
