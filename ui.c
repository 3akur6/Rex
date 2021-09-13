#include "components/rex_begin_scene.c"
#include "components/rex_main_scene.c"
#include "components/rex_end_scene.c"

/* 
define ui scenes 
*/
enum ui_scene
{
    REX_BEGIN_SCENE,
    REX_MAIN_SCENE,
    REX_END_SCENE
};

static enum ui_scene current_scene;

/* prepare some static variables */
void ui_init(struct nk_context *ctx)
{
    /* load font */
    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&atlas);

        { /* add new fonts here */
            rex_fonts[0].font = nk_font_atlas_add_from_file(atlas, "fonts/DroidSans.ttf", 32, 0);
            rex_fonts[0].height = 32;
        }

        nk_glfw3_font_stash_end();
        nk_style_set_font(ctx, &rex_fonts[0].font->handle);
    }

    return;
}

void ui_run(struct nk_context *ctx, float width, float height)
{
    /* draw current scene */
    switch (current_scene)
    {
    case REX_BEGIN_SCENE:
        /* handle begin scene event */
        switch (rex_begin_scene(ctx, width, height))
        {
        case REX_BEGIN_SCENE_SPACE_PRESSED:
            /* ensure all locks free */
            goto REX_GOTO_END_SCENE;
        default:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
    case REX_MAIN_SCENE:
        switch (rex_main_scene(ctx, width, height))
        {
        default:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
    case REX_END_SCENE:
        switch (rex_end_scene(ctx, width, height))
        {
        case REX_END_SCENE_SPACE_PRESSED:
            /* ensure all locks free */
            goto REX_GOTO_MAIN_SCENE;
        default:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
    default:
        goto REX_GOTO_BEGIN_SCENE;
    }

/* draw begin scene */
REX_GOTO_BEGIN_SCENE:
    current_scene = REX_BEGIN_SCENE;
    return;
/* draw main scene */
REX_GOTO_MAIN_SCENE:
    current_scene = REX_MAIN_SCENE;
    return;
/* draw end scene */
REX_GOTO_END_SCENE:
    current_scene = REX_END_SCENE;
    return;
REX_GOTO_NOTHING_HAPPEN:
    return;
}
