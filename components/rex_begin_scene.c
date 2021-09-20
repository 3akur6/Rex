enum rex_begin_scene_event
{
    REX_BEGIN_SCENE_NOTHING_HAPPEN,
    REX_BEGIN_SCENE_SPACE_PRESSED, /* space pressed, ignore the difference between holding and pressing */
};

/* draw prompt text */
void rex_begin_scene_prompt_text(struct nk_context *ctx, float x, float y)
{
    /* set the style of the start button*/
    set_style(ctx, THEME_PROMPT_TEXT);

    if (nk_begin(ctx, "Prompt Text", nk_rect(x, y, BEGIN_SCENE_PROMT_TEXT_WIDTH, BEGIN_SCENE_PROMT_TEXT_HEIGHT), NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, BEGIN_SCENE_PROMT_TEXT_ROW_HEIGHT, 1);

        /* set font */
        nk_style_set_font(ctx, &rex_fonts[0].font->handle);

        nk_label(ctx, "PRESS SPACE TO START", NK_TEXT_CENTERED);
    }
    nk_end(ctx);
}

enum rex_begin_scene_event rex_begin_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_begin_scene_event event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
    /* change style here if necessary */
    set_style(ctx, THEME_ALL_SCENES);

    /* draw scene here */
    rex_begin_scene_prompt_text(ctx, BEGIN_SCENE_PROMT_TEXT_X, BEGIN_SCENE_PROMT_TEXT_Y);
    /* draw background */
    nk_begin(ctx, BEGIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    /* only init once */
    rex_game_init_trex();

    if (rex_scene_lock == nk_false)
    {
        rex_game_set_trex_status(REX_GAME_TREX_STATIC);
        /* detect event */
        /* detect space event */
        switch (rex_input_key.code)
        {
        case REX_KEY_CODE_DOWN:
            break;
        case REX_KEY_CODE_SPACE:
            switch (rex_input_key.status)
            {
            case REX_KEY_STATUS_REPEAT:
            case REX_KEY_STATUS_PRESS:
                /* play sound */
                cs_play_sound(rex_sound_ctx, rex_sounds[SOUND_PRESS_ID]);
                /* event lock */
                rex_scene_lock = nk_true;
                /* set trex status to jump */
                rex_game_set_trex_status(REX_GAME_TREX_JUMP);
                break;
            case REX_KEY_STATUS_RELEASE:
                break;
            }

            break;
        default:
            event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
        }
    }

    rex_game_draw_objects(ctx);
    /* must be place in the background window */
    /* first jump */
    if (rex_scene_lock == nk_true)
    {
        rex_begin_frames();

        struct rex_game_object *trex = rex_object_get_trex();

        if (trex->detail.trex != REX_GAME_TREX_JUMP)
        { /* trex finishes jumping */
            rex_scene_lock = nk_false;
            event = REX_BEGIN_SCENE_SPACE_PRESSED;
            rex_end_frames();

            goto NK_BEGIN_SCENE_GOTO_NK_END;
        }
    }
    rex_draw_subimage(ctx, IMAGE_HORIZON_ID, 0, 0, BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH, IMAGE_HORIZON_HEIGHT, BEGIN_SCENE_HORIZON_X, BEGIN_SCENE_HORIZON_Y);

NK_BEGIN_SCENE_GOTO_NK_END:
    nk_end(ctx);

    return event;
}
