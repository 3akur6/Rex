enum rex_main_scene_event
{
    REX_MAIN_SCENE_NOTHING_HAPPEN,
};

enum rex_main_scene_event rex_main_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_main_scene_event event = REX_MAIN_SCENE_NOTHING_HAPPEN;

    /* draw scene here */
    nk_begin(ctx, MAIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    nk_layout_row_dynamic(ctx, 30, 1);
    nk_label(ctx, MAIN_SCENE_NAME, NK_TEXT_CENTERED);

    nk_end(ctx);

    return event;
}