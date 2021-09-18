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
            rex_fonts[0].font = nk_font_atlas_add_from_file(atlas, "fonts/Apple.ttf", 30, 0);
            rex_fonts[0].height = 30;
        }

        nk_glfw3_font_stash_end();
        nk_style_set_font(ctx, &rex_fonts[0].font->handle);
    }

    { /* calc jump distance array */
        need_frames_amount_one_way = (int)sqrt((2 * REX_GAME_JUMP_HEIGHT) / REX_GAME_GRAVITY);
        rex_game_trex_generate_jump_distance_array();
    }

    { /* register keyboard event here */
        rex_keyboard_register_keyboard_events();
    }

    return;
}

void ui_run(struct nk_context *ctx, float width, float height)
{
    unsigned char event;
    /* draw current scene */
    switch (current_scene)
    {
    case REX_BEGIN_SCENE:
        /* handle begin scene event */
        event = rex_begin_scene(ctx, width, height);
        switch (event)
        {
        case REX_BEGIN_SCENE_SPACE_PRESSED:
            goto REX_GOTO_MAIN_SCENE;
        default:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
    case REX_MAIN_SCENE:
        event = rex_main_scene(ctx, width, height);
        switch (event)
        {
        case REX_MAIN_SCENE_GAME_OVER:
            goto REX_GOTO_END_SCENE;
        default:
            goto REX_GOTO_NOTHING_HAPPEN;
        }
    case REX_END_SCENE:
        event = rex_end_scene(ctx, width, height);
        switch (event)
        {
        case REX_END_SCENE_SPACE_PRESSED:
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
{ /* reset */
    for (unsigned int i = 1; i < REX_GAME_MAX_OBJECT_AMOUNT; i++)
        rex_objects[i].active = nk_false;

    rex_current_score = 0;
    rex_end_frames();
}

    current_scene = REX_MAIN_SCENE;
    return;
/* draw end scene */
REX_GOTO_END_SCENE:
    /* update hi_score */
    if (rex_hi_score < rex_current_score)
        rex_hi_score = rex_current_score;

    current_scene = REX_END_SCENE;
    return;
REX_GOTO_NOTHING_HAPPEN:
    return;
}
