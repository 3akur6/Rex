void rex_horizon_line_roll(struct nk_context *ctx, float x, float y)
{
    /* horizon line offset in x */
    rex_horizon_line_offset = (rex_horizon_line_offset + rex_game_speed * REX_GAME_HORIZON_LINE_ROLL_SPEED) % IMAGE_HORIZON_WIDTH;

    float window_width = glfw.width;
    float split = IMAGE_HORIZON_WIDTH - window_width;

    if (rex_horizon_line_offset <= split)
    {
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, rex_horizon_line_offset, 0, window_width, IMAGE_HORIZON_HEIGHT, x, y);
    }
    else
    {
        float part1_width = IMAGE_HORIZON_WIDTH - rex_horizon_line_offset;
        float part2_width = window_width - part1_width;
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, rex_horizon_line_offset, 0, part1_width, IMAGE_HORIZON_HEIGHT, x, y);
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, 0, 0, part2_width, IMAGE_HORIZON_HEIGHT, x + part1_width, y);
    }
}
