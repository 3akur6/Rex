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

    { /* handle event here */
        int space_status = rex_get_space_status();

        /* detect event */
        /* detect space event */
        switch (space_status)
        {
        case REX_KEY_HOLD:
        case REX_KEY_PRESS:
            /* event lock */
            rex_game_set_trex_status(REX_GAME_TREX_JUMP);

            break;
        case REX_KEY_RELEASE:
        default:
            event = REX_BEGIN_SCENE_NOTHING_HAPPEN;
        }
    }

    {
        /* must be place in the background window */
        /* jump */
        rex_begin_frames();

        struct rex_game_object *trex = rex_object_get_trex();

        if (trex->detail.trex != REX_GAME_TREX_JUMP)
            rex_game_set_trex_status(REX_GAME_TREX_WALK);

        /* try to generate a random obstacle in rex_objects */
        rex_game_generate_random_object();

        rex_game_draw_objects(ctx);

        rex_main_scene_hi_score(ctx, MAIN_SCENE_HI_SCORE_X, MAIN_SCENE_HI_SCORE_Y);
        /* draw instant score */
        rex_draw_number(ctx, rex_current_score, REX_GAME_SCORE_DIGIT_WIDTH, MAIN_SCENE_CURRENT_SCORE_X, MAIN_SCENE_CURRENT_SCORE_Y);
        /* score increases */
        rex_game_score_update();

        if (rex_game_collision_detect() == nk_true)
            event = REX_MAIN_SCENE_GAME_OVER;

        rex_horizon_line_roll(ctx, MAIN_SCENE_HORIZON_X, MAIN_SCENE_HORIZON_Y);
    }

    nk_end(ctx);

    return event;
}