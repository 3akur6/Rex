enum rex_end_scene_event
{
    REX_END_SCENE_NOTHING_HAPPEN,
    REX_END_SCENE_SPACE_PRESSED,
};

void rex_end_scene_hi(struct nk_context *ctx, float place_x, float place_y)
{
    unsigned int offset = 10 * IMAGE_TEXT_SPRITE_DIGIT_OFFSET;
    rex_draw_subimage(ctx, IMAGE_TEXT_SPRITE_ID, (float)offset, 0, IMAGE_TEXT_SPRITE_DIGIT_OFFSET + IMAGE_TEXT_SPRITE_DIGIT_WIDTH, IMAGE_TEXT_SPRITE_HEIGHT, place_x, place_y);
}

void rex_end_scene_hi_score(struct nk_context *ctx, float place_x, float place_y)
{
    rex_end_scene_hi(ctx, place_x, place_y);
    rex_draw_number(ctx, rex_hi_score, REX_GAME_SCORE_DIGIT_WIDTH, place_x + IMAGE_TEXT_SPRITE_DIGIT_OFFSET + IMAGE_TEXT_SPRITE_DIGIT_WIDTH + END_SCENE_GAP_BETWEEN_HI_SCORE, place_y);
}

enum rex_end_scene_event rex_end_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_end_scene_event event = REX_END_SCENE_NOTHING_HAPPEN;

    /* detect event first */
    /* detect space event */
    int space_status = rex_get_space_status();
    if (rex_scene_lock == nk_false)
    {
        switch (space_status)
        {
        case REX_KEY_HOLD:
        case REX_KEY_PRESS:
            rex_scene_lock = nk_true;

            break;
        case REX_KEY_RELEASE:
        default:
            event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
        }
    }

    /* change style of the third scene */
    // set_style(ctx, THEME_WHITE);

    /* draw scene here */
    nk_begin(ctx, END_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);
    {
        /* draw images */
        rex_draw_image(ctx, IMAGE_GAME_OVER_TEXT_ID, END_SCENE_GAME_OVER_X, END_SCENE_GAME_OVER_Y);
        rex_draw_image(ctx, IMAGE_RESTART_ID, END_SCENE_RESTART_X, END_SCENE_RESTART_Y);
        rex_draw_image(ctx, IMAGE_TREX_7_ID, END_SCENE_TREX_X, END_SCENE_HORIZON_Y - END_SCENE_FALL_BETWEEN_TREX_HORIZON);
        /* draw hi score */
        rex_end_scene_hi_score(ctx, END_SCENE_HI_SCORE_X, END_SCENE_HI_SCORE_Y);
        /* draw current score */
        rex_draw_number(ctx, rex_current_score, REX_GAME_SCORE_DIGIT_WIDTH, END_SCENE_CURRENT_SCORE_X, END_SCENE_CURRENT_SCORE_Y);
    }
    nk_end(ctx);

    if (rex_scene_lock == nk_true)
    {
        /* do something here before scene changes */

        /* event lock free */
        rex_scene_lock = nk_false;
        event = REX_END_SCENE_SPACE_PRESSED;
    }

    return event;
}
