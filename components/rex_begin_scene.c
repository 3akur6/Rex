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

        nk_label(ctx, "press space to start", NK_TEXT_CENTERED);
    }
    nk_end(ctx);
}

void rex_begin_scene_not_jump(struct nk_context *ctx)
{
    rex_draw_image(ctx, IMAGE_TREX_2_ID, BEGIN_SCENE_TREX_X, BEGIN_SCENE_HORIZON_Y - BEGIN_SCENE_FALL_BETWEEN_TREX_HORIZON);
    rex_draw_subimage(ctx, IMAGE_HORIZON_ID, 0, 0, BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH, IMAGE_HORIZON_HEIGHT, BEGIN_SCENE_HORIZON_X, BEGIN_SCENE_HORIZON_Y);
}

void rex_begin_scene_first_jump(struct nk_context *ctx)
{
    rex_trex_jump(ctx, IMAGE_TREX_2_ID, BEGIN_SCENE_TREX_X, BEGIN_SCENE_HORIZON_Y - BEGIN_SCENE_FALL_BETWEEN_TREX_HORIZON);
    rex_draw_subimage(ctx, IMAGE_HORIZON_ID, 0, 0, BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH, IMAGE_HORIZON_HEIGHT, BEGIN_SCENE_HORIZON_X, BEGIN_SCENE_HORIZON_Y);
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

    int space_status = rex_get_space_status();
    if (rex_scene_lock == nk_false)
    {
        /* detect event */
        /* detect space event */
        switch (space_status)
        {
        case REX_KEY_HOLD:
        case REX_KEY_PRESS:
            /* event lock */
            rex_scene_lock = nk_true;

            break;
        case REX_KEY_RELEASE:
        default:
            event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
        }
    }

    /* must be place in the background window */
    /* first jump */
    if (rex_scene_lock == nk_true)
    {
        rex_begin_frames();
        if (rex_trex_jump(ctx, IMAGE_TREX_2_ID, BEGIN_SCENE_TREX_X, BEGIN_SCENE_TREX_Y - BEGIN_SCENE_FALL_BETWEEN_TREX_HORIZON) == nk_true)
        { /* trex finishes jumping */
            rex_scene_lock = nk_false;
            event = REX_BEGIN_SCENE_SPACE_PRESSED;
            rex_end_frames();

            goto NK_BEGIN_SCENE_GOTO_NK_END;
        }
        rex_draw_subimage(ctx, IMAGE_HORIZON_ID, 0, 0, BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH, IMAGE_HORIZON_HEIGHT, BEGIN_SCENE_HORIZON_X, BEGIN_SCENE_HORIZON_Y);
    }
    else
        rex_begin_scene_not_jump(ctx);

NK_BEGIN_SCENE_GOTO_NK_END:
    nk_end(ctx);

    return event;
}
