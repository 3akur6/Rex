enum rex_main_scene_event
{
    REX_MAIN_SCENE_NOTHING_HAPPEN,
};

enum rex_main_scene_event rex_main_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_main_scene_event event = REX_MAIN_SCENE_NOTHING_HAPPEN;

    /* change style of the second scene*/
    set_style(ctx, THEME_WHITE);

    /* draw scene here */
    nk_begin(ctx, MAIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    {
        rex_begin_frames();

        rex_trex_walk(ctx, 4, 100);
        rex_horizon_line_roll(ctx, 4, 100);

        if (rex_obstackle_amount < REX_GAME_MAX_OBSTACKLE_AMOUNT && rex_frame)
        {
            /* get random obstackle type */
            enum rex_game_obstackle_type type = rex_game_random_obstackle();
            switch (type)
            {
            case REX_GAME_OBSTACKLE_PTERODACTYL:
                rex_event_lock = nk_true;
            case REX_GAME_OBSTACKLE_CACTUS_SMALL_0:
            case REX_GAME_OBSTACKLE_CACTUS_SMALL_1:
            case REX_GAME_OBSTACKLE_CACTUS_SMALL_2:
            case REX_GAME_OBSTACKLE_CACTUS_LARGE_0:
            case REX_GAME_OBSTACKLE_CACTUS_LARGE_1:
            case REX_GAME_OBSTACKLE_CACTUS_LARGE_2:
            }
        }

        // if (rex_event_lock == nk_true)
        // {
        //     for ()
        // }
    }

    nk_end(ctx);

    return event;
}