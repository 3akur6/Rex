enum rex_end_scene_event
{
    REX_END_SCENE_NOTHING_HAPPEN,
    REX_END_SCENE_SPACE_PRESSED,
};

void rex_end_scene_hi(struct nk_context *ctx, float place_x, float place_y)
{
    unsigned int offset = 10 * IMAGE_TEXT_SPRITE_DIGIT_OFFSET;
    rex_draw_subimage(ctx, IMAGE_TEXT_SPRITE_PATH, (float)offset, 0, IMAGE_TEXT_SPRITE_DIGIT_OFFSET + IMAGE_TEXT_SPRITE_DIGIT_WIDTH, IMAGE_TEXT_SPRITE_HEIGHT, place_x, place_y);
}

void rex_end_scene_hi_score(struct nk_context *ctx, float place_x, float place_y)
{
    rex_end_scene_hi(ctx, place_x, place_y);
    rex_draw_number(ctx, rex_hi_score, place_x + IMAGE_TEXT_SPRITE_DIGIT_OFFSET + IMAGE_TEXT_SPRITE_DIGIT_WIDTH + END_SCENE_GAP_BETWEEN_HI_SCORE, place_y);
}

enum rex_end_scene_event rex_end_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_end_scene_event event = REX_END_SCENE_NOTHING_HAPPEN;

    /* draw scene here */
    nk_begin(ctx, END_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);
    {
        /* draw images */
        rex_draw_image(ctx, IMAGE_GAME_OVER_TEXT_PATH, 50, 0);
        rex_draw_image(ctx, IMAGE_RESTART_PATH, 100, 100);
        rex_draw_image(ctx, IMAGE_TREX_7_PATH, 200, 200);
        /* draw hi score */
        rex_end_scene_hi_score(ctx, 300, 100);
        /* draw current score */
        rex_draw_number(ctx, rex_current_score, 550, 100);
    }
    nk_end(ctx);

    /* detect event */
    /* detect space event */
    switch (rex_get_space_status())
    {
    case REX_KEY_HOLD:
    case REX_KEY_PRESS:
        /* send space pressed message to UI */
        event = REX_BEGIN_SCENE_SPACE_PRESSED;
        break;
    case REX_KEY_RELEASE:
    default:
        event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
    }

    return event;
}
