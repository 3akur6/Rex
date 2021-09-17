#include "../libs/collision.c"

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

    { /* handle event here */
        int space_status = rex_get_space_status();

        /* detect event */
        /* detect space event */
        switch (space_status)
        {
        case REX_KEY_HOLD:
        case REX_KEY_PRESS:
            /* event lock */
            rex_game_set_trex_status(REX_GAME_TREX_JUMP);

            break;
        case REX_KEY_RELEASE:
        default:
            event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
        }
    }

    {
        /* must be place in the background window */
        /* jump */
        rex_begin_frames();

        struct rex_game_object *trex = rex_object_get_trex();

        if (trex->detail.trex != REX_GAME_TREX_JUMP)
            rex_game_set_trex_status(REX_GAME_TREX_WALK);

        /* try to generate a random obstacle in rex_objects */
        rex_game_generate_random_object();

        rex_game_draw_objects(ctx);
        // rex_object_trex_jump(ctx, trex);
        /* draw instant score */
        rex_draw_number(ctx, rex_current_score, REX_GAME_SCORE_DIGIT_WIDTH, MAIN_SCENE_CURRENT_SCORE_X, MAIN_SCENE_CURRENT_SCORE_Y);
        /* score increases */
        rex_game_score_update();

        if (rex_game_collision_detect() == nk_true)
            rex_draw_number(ctx, 666, 3, 5, 2);

        rex_horizon_line_roll(ctx, MAIN_SCENE_HORIZON_X, MAIN_SCENE_HORIZON_Y);
    }

    nk_end(ctx);

    return event;
}