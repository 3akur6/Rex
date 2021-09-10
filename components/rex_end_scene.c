enum rex_end_scene_event
{
    REX_END_SCENE_NOTHING_HAPPEN,
};

enum rex_end_scene_event rex_end_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_end_scene_event event = REX_END_SCENE_NOTHING_HAPPEN;

    /* draw scene here */

    return event;
}