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

    { /* generate random seed by time */
        srand((unsigned int)time(NULL));
        rex_random_seed = rand();
    }

    { /* init sound context and load sound files */
        unsigned int frequency = 44100;
        int buffered_samples = 16; /* set small buffer size to flush quickly */
        int playing_pool_count = SOUND_AMOUNT;

        rex_sound_ctx = cs_make_context(NULL, frequency, buffered_samples, playing_pool_count, NULL);
        cs_spawn_mix_thread(rex_sound_ctx);

        for (unsigned char i = 0; i < playing_pool_count; i++)
        {
            rex_sounds_buf[i] = cs_load_ogg(rex_sound_path_list[i]);
            if (rex_sounds_buf[i].channels[0] == NULL)
                fprintf(stderr, "[cs_load_ogg] %s\n", cs_error_reason);

            rex_sounds[i] = cs_make_def(&rex_sounds_buf[i]);
        }
    }
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
    /* regenerate random seed */
    srand((unsigned int)time(NULL));
    rex_random_seed = rand();

    /* clear all objects except trex in queue */
    for (unsigned int i = 0; i < REX_GAME_MAX_OBJECT_AMOUNT - 1; i++)
        rex_objects[i].active = INACTIVE;

    /* reset trex */
    struct rex_game_object *trex = rex_object_get_trex();
    trex->active = ACTIVE;
    trex->create_at_frame = 0;
    trex->destroy_at_frame = 0;

    /* only init once */
    rex_object_init_horizon();
    /* set horizon to active */
    struct rex_game_object_horizon *horizon = rex_object_get_horizon();
    horizon->active = ACTIVE;

    rex_current_score = 0;
    rex_game_speed = REX_GAME_SPEED;
}

    current_scene = REX_MAIN_SCENE;
    return;

/* draw end scene */
REX_GOTO_END_SCENE:
    /* update hi_score */
    if (rex_hi_score < rex_current_score)
        rex_hi_score = rex_current_score;

    /* freeze all objects */
    rex_game_freeze_objects();
    /* freeze horizon */
    rex_object_freeze_horizon();

    current_scene = REX_END_SCENE;
    return;

REX_GOTO_NOTHING_HAPPEN:
    return;
}
