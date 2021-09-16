enum rex_main_scene_event
{
    REX_MAIN_SCENE_NOTHING_HAPPEN,
    REX_MAIN_SCENE_SPACE_PRESSED
};

enum rex_main_scene_event rex_main_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_main_scene_event event = REX_MAIN_SCENE_NOTHING_HAPPEN;

    /* change style of the second scene*/
    //set_style(ctx, THEME_PROMPT_TEXT);

    /* draw scene here */
    nk_begin(ctx, MAIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    // { /* handle event here */
    //     int space_status = rex_get_space_status();
    //     if (rex_scene_lock == nk_false)
    //     {
    //         /* detect event */
    //         /* detect space event */
    //         switch (space_status)
    //         {
    //         case REX_KEY_HOLD:
    //         case REX_KEY_PRESS:
    //             /* event lock */
    //             rex_scene_lock = nk_true;

    //             break;
    //         case REX_KEY_RELEASE:
    //         default:
    //             event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
    //         }
    //     }
    // }

    {
        rex_begin_frames();

        /* must be place in the background window */
        /* jump */
        // if (rex_scene_lock == nk_true)
        // {
        //     rex_begin_frames();
        //     struct rex_game_object *trex = rex_object_get_trex();
        //     rex_object_trex_jump(ctx, trex);

        //     if (trex->detail.trex != REX_GAME_TREX_JUMP)
        //     { /* trex finishes jumping */
        //         rex_scene_lock = nk_false;

        //         trex->detail.trex = REX_GAME_TREX_WALK;
        //     }
        // }

        // rex_game_set_trex_status(REX_GAME_TREX_WALK);

        // struct rex_game_object *trex = &rex_objects[0];
        rex_game_init_trex();
        //rex_game_set_trex_status(REX_GAME_TREX_JUMP);
        /* try to generate a random obstacle in rex_objects */
        rex_game_generate_random_object();

        rex_debug_print_rex_objects();

        rex_draw_number(ctx, rex_frame, 5, 0, 0);

        rex_game_draw_objects(ctx);
        // rex_object_trex_jump(ctx, trex);
        /* draw instant score */
        rex_draw_number(ctx, 666, REX_GAME_SCORE_DIGIT_WIDTH, MAIN_SCENE_CURRENT_SCORE_X, MAIN_SCENE_CURRENT_SCORE_Y);

        rex_horizon_line_roll(ctx, MAIN_SCENE_HORIZON_X, MAIN_SCENE_HORIZON_Y);
    }

    nk_end(ctx);

    return event;
}