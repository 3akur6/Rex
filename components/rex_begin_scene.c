enum rex_begin_scene_event
{
    REX_BEGIN_SCENE_NOTHING_HAPPEN,
};

void rex_begin_scene_rex_static(struct nk_context *ctx)
{
    struct nk_image image = nk_gl_image_load(BEGIN_SCENE_REX_STATIC_IMAGE_PATH);
}

enum rex_begin_scene_event rex_begin_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_begin_scene_event event = REX_BEGIN_SCENE_NOTHING_HAPPEN;

    /* change style here if necessary */

    /* draw scene here */
    if (nk_begin(ctx, BEGIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BORDER))
    {
        // rex_begin_scene_rex_static(ctx);
    }
    nk_end(ctx);

    return event;
}