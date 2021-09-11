enum rex_end_scene_event
{
    REX_END_SCENE_NOTHING_HAPPEN,
};

enum rex_end_scene_event rex_end_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_end_scene_event event = REX_END_SCENE_NOTHING_HAPPEN;

    /* draw scene here */
    nk_begin(ctx, END_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);
    {
        /* draw images */
        rex_draw_subimage(ctx, OBJECTS_IMAGE_PATH, RESTART_X, RESTART_Y, 100, 100, 0, 0);
    }
    nk_end(ctx);

    return event;
}