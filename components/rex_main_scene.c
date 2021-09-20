#include "../libs/collision.c"

enum rex_main_scene_event
{
    REX_MAIN_SCENE_NOTHING_HAPPEN,
    REX_MAIN_SCENE_GAME_OVER
};

void rex_main_scene_hi(struct nk_context *ctx, float place_x, float place_y)
{
    unsigned int offset = 10 * IMAGE_TEXT_SPRITE_DIGIT_OFFSET;
    rex_draw_subimage(ctx, IMAGE_TEXT_SPRITE_ID, (float)offset, 0, IMAGE_TEXT_SPRITE_DIGIT_OFFSET + IMAGE_TEXT_SPRITE_DIGIT_WIDTH, IMAGE_TEXT_SPRITE_HEIGHT, place_x, place_y);
}

void rex_main_scene_hi_score(struct nk_context *ctx, float place_x, float place_y)
{
    rex_main_scene_hi(ctx, place_x, place_y);
    rex_draw_number(ctx, rex_hi_score, REX_GAME_SCORE_DIGIT_WIDTH, place_x + IMAGE_TEXT_SPRITE_DIGIT_OFFSET + IMAGE_TEXT_SPRITE_DIGIT_WIDTH + END_SCENE_GAP_BETWEEN_HI_SCORE, place_y);
}

enum rex_main_scene_event rex_main_scene(struct nk_context *ctx, float window_width, float window_height)
{
    enum rex_main_scene_event event = REX_MAIN_SCENE_NOTHING_HAPPEN;

    /* change style of the second scene*/
    //set_style(ctx, THEME_PROMPT_TEXT);

    /* draw scene here */
    nk_begin(ctx, MAIN_SCENE_NAME, nk_rect(0, 0, window_width, window_height), NK_WINDOW_BACKGROUND);

    if (rex_scene_lock == nk_false)
    { /* handle event */
        switch (rex_input_key.code)
        {
        case REX_KEY_CODE_DOWN:
            switch (rex_input_key.status)
            {
            case REX_KEY_STATUS_REPEAT:
            case REX_KEY_STATUS_PRESS:
                /* set trex status to duck */
                rex_game_set_trex_status(REX_GAME_TREX_DUCK);
                break;
            case REX_KEY_STATUS_RELEASE:
                rex_game_set_trex_status(REX_GAME_TREX_WALK);
                break;
            }

            break;
        case REX_KEY_CODE_SPACE:
            switch (rex_input_key.status)
            {
            case REX_KEY_STATUS_REPEAT:
            case REX_KEY_STATUS_PRESS:
                rex_scene_lock = nk_true;
                /* play press sound */
                cs_play_sound(rex_sound_ctx, rex_sounds[SOUND_PRESS_ID]);
                /* set trex status to jump */
                rex_game_set_trex_status(REX_GAME_TREX_JUMP);
                break;
            case REX_KEY_STATUS_RELEASE:
                break;
            }

            break;
        default:
            event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
        }
    }

    {
        /* must be place in the background window */
        /* jump */
        rex_begin_frames();

        struct rex_game_object *trex = rex_object_get_trex();

        /* meaningless status */
        if (trex->detail.trex == 0)
        {
            rex_scene_lock = nk_false;
            rex_game_set_trex_status(REX_GAME_TREX_WALK);
        }

        /* try to generate a random obstacle in rex_objects */
        rex_game_generate_random_objects();

        rex_debug_print_rex_objects();

        /* draw horizon */
        rex_object_draw_horizon(ctx);

        rex_game_draw_objects(ctx);

        rex_main_scene_hi_score(ctx, MAIN_SCENE_HI_SCORE_X, MAIN_SCENE_HI_SCORE_Y);
        /* draw instant score */
        rex_draw_number(ctx, rex_current_score, REX_GAME_SCORE_DIGIT_WIDTH, MAIN_SCENE_CURRENT_SCORE_X, MAIN_SCENE_CURRENT_SCORE_Y);
        /* score increases */
        rex_game_score_update();

        if (rex_current_score % REX_GAME_LEVEL_UP_PER_SCORES == 0 && rex_current_score != 0)
        {
            /* play sound */
            cs_play_sound(rex_sound_ctx, rex_sounds[SOUND_REACHED_ID]);
            /* level up, speed up */
            rex_game_speed += REX_GAME_SPEED_ADDEND;
        }

        /* handle collision detect here */
        // if (rex_game_collision_detect() == nk_true)
        // {
        //     /* play sound */
        //     cs_play_sound(rex_sound_ctx, rex_sounds[SOUND_HIT_ID]);
        //     event = REX_MAIN_SCENE_GAME_OVER;
        //     rex_end_frames();
        // }
    }

    nk_end(ctx);

    return event;
}