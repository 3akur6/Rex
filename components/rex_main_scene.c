enum rex_main_scene_event
{
    REX_MAIN_SCENE_NOTHING_HAPPEN,
};

enum rex_main_scene_event rex_main_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_main_scene_event event = REX_MAIN_SCENE_NOTHING_HAPPEN;

    /* change style of the second scene*/
    set_style(ctx, THEME_PROMPT_TEXT);

    /* draw scene here */
    nk_begin(ctx, MAIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    {
        rex_begin_frames();

        /* try to generate a random obstackle in rex_obstackles */
        rex_game_generate_random_obstackle();

        rex_game_draw_obstackles(ctx);

        rex_trex_walk(ctx, MAIN_SCENE_TREX_X, MAIN_SCENE_HORIZON_Y - MAIN_SCENE_FALL_BETWEEN_TREX_HORIZON);
        rex_horizon_line_roll(ctx, MAIN_SCENE_HORIZON_X, MAIN_SCENE_HORIZON_Y);
    }

    nk_end(ctx);

    return event;
}