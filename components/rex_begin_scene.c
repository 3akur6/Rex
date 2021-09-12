enum rex_begin_scene_event
{
    REX_BEGIN_SCENE_NOTHING_HAPPEN,
    REX_BEGIN_SCENE_SPACE_PRESSED, /* space pressed, ignore the difference between holding and pressing */
};

/* draw prompt text */
void rex_begin_scene_prompt_text(struct nk_context *ctx, float x, float y)
{
    /* set the style of the start button*/
    set_style(ctx, THEME_BLACK);

    if (nk_begin(ctx, "Prompt Text", nk_rect(x, y, 300, 100), NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, 30, 1);

        /* set font */
        nk_style_set_font(ctx, &rex_fonts[0].font->handle);

        nk_label(ctx, "press space to start", NK_TEXT_CENTERED);
    }
    nk_end(ctx);
}

void rex_begin_scene_rex_static(struct nk_context *ctx, float x, float y)
{
    struct nk_command_buffer *canvas;
    struct nk_rect rect;

    canvas = nk_window_get_canvas(ctx);

    struct rex_image image = rex_image_load(BEGIN_SCENE_REX_STATIC_IMAGE_PATH);

    int image_width = image.width;
    int image_height = image.height;

    rect = nk_rect(x, y, image_width, image_height); /* create rect to draw image */
    nk_draw_image(canvas, rect, &image.handle, nk_white);
}

enum rex_begin_scene_event rex_begin_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_begin_scene_event event = REX_BEGIN_SCENE_NOTHING_HAPPEN;

    /* load font */
    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&atlas);
        for (int i = 0; i < 7; i++)
        {
            rex_fonts[i].font = nk_font_atlas_add_from_file(atlas,
                                                            "fonts/DroidSans.ttf", (i + 1) * 8, 0);
            rex_fonts[i].height = (i + 1) * 8;
        }

        nk_glfw3_font_stash_end();
        nk_style_set_font(ctx, &rex_fonts[0].font->handle);
    }

    /* change style here if necessary */
    set_style(ctx, THEME_WHITE);

    /* draw scene here */
    /* draw background */
    nk_begin(ctx, BEGIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    /* must be place in the background window */
    rex_draw_image(ctx, BEGIN_SCENE_REX_STATIC_IMAGE_PATH, 600, 100);

    nk_end(ctx);

    rex_begin_scene_prompt_text(ctx, 120, 120);

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