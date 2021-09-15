void rex_pterodactyl_fly(struct nk_context *ctx, float x, float y)
{
    if (rex_frame & REX_GAME_PTERODACTYL_REFRESH_SPEED)
        rex_draw_image(ctx, IMAGE_PTERODACTYL_0_ID, x, y);
    else
        rex_draw_image(ctx, IMAGE_PTERODACTYL_1_ID, x, y);

    return;
}
