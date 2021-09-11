#include "components/rex_begin_scene.c"
#include "components/rex_main_scene.c"
#include "components/rex_end_scene.c"
#include "overview.c"

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
void ui_init(void)
{
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
        case REX_BEGIN_SCENE_NOTHING_HAPPEN:
            goto REX_GOTO_NOTHING_HAPPEN;
        case REX_BEGIN_SCENE_SPACE_PRESSED:
            goto REX_GOTO_END_SCENE;
        }
        return;
    case REX_MAIN_SCENE:
        switch (rex_main_scene(ctx, width, height))
        {
        case REX_MAIN_SCENE_NOTHING_HAPPEN:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
        return;
    case REX_END_SCENE:
        switch (rex_end_scene(ctx, width, height))
        {
        case REX_END_SCENE_NOTHING_HAPPEN:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
        return;
    default:
        goto REX_GOTO_BEGIN_SCENE;
    }

/* draw begin scene */
REX_GOTO_BEGIN_SCENE:
    current_scene = REX_BEGIN_SCENE;
    rex_begin_scene(ctx, width, height);
    return;
/* draw main scene */
REX_GOTO_MAIN_SCENE:
    current_scene = REX_MAIN_SCENE;
    rex_main_scene(ctx, width, height);
    return;
/* draw end scene */
REX_GOTO_END_SCENE:
    current_scene = REX_END_SCENE;
    rex_end_scene(ctx, width, height);
    return;
REX_GOTO_NOTHING_HAPPEN:
    return;
}
