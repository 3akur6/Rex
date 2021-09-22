#ifndef UI_H_
#define UI_H_

/* refresh after draw cycles */
#define REFRESH_CYCLES 1
#define MAX_FRAME_AMOUNT 2000

/* max buffer size of images */
#define MAX_IMAGES_AMOUNT 50

/* max buffer size of path name */
#define MAX_PATH_LENGTH 50

/* predefine window width and height */
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

/* game settings */
#define REX_GAME_MAX_GAME_SPEED 1.6f
#define REX_GAME_SPEED_ADDEND 0.01f
#define REX_GAME_LEVEL_UP_PER_SCORES 100 /* level up per scores */
#define REX_GAME_GRAVITY 0.7f
#define REX_GAME_JUMP_HEIGHT 200
#define REX_GAME_JUMP_STEP 2
#define REX_GAME_TREX_WALK_SPEED 0x8
#define REX_GAME_TREX_DUCK_SPEED REX_GAME_TREX_WALK_SPEED
#define REX_GAME_PTERODACTYL_REFRESH_SPEED 0x8

/* pterodactyl fly height (base on horizon line) */
#define REX_GAME_PTERODACTYL_MAX_HEIGHT 140
#define REX_GAME_PTERODACTYL_MIN_HEIGHT 50

#define REX_GAME_CREATE_OBJECT_GAP_BETWEEN_MIN_AND_MAX 10

/* speed */
#define REX_GAME_PTERODACTYL_SPEED 7
#define REX_GAME_CLOUD_SPEED 2
#define REX_GAME_HORIZON_LINE_ROLL_SPEED 7
#define REX_GAME_HORIZON_LINE_EXTEND_SPEED 50
#define REX_GAME_OBJECT_MOVE_SPEED REX_GAME_HORIZON_LINE_ROLL_SPEED
#define REX_GAME_SPEED 1

#define REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MAX 1000
#define REX_GAME_CREATE_OBSTACLE_AFTER_FRAME_MIN 1

#define REX_GAME_OBJECT_TYPE_AMOUNT 3
#define REX_GAME_OBSTACLE_TYPE_AMOUNT 7
#define REX_GAME_DECORATION_TYPE_AMOUNT 1

#define REX_GAME_MAX_OBSTACLE_AMOUNT 4   /* define the max amount of obstacles drew in one frame */
#define REX_GAME_MAX_DECORATION_AMOUNT 4 /* define the max amount of decorations drew in one frame */

/* additional place for trex at index (REX_GAME_MAX_OBJECT_AMOUNT - 1)
 */
#define REX_GAME_MAX_OBJECT_AMOUNT (REX_GAME_MAX_OBSTACLE_AMOUNT + REX_GAME_MAX_DECORATION_AMOUNT + 1)
#define REX_GAME_OBJECT_TREX_INDEX (REX_GAME_MAX_OBJECT_AMOUNT - 1)

/* trex */
#define REX_GAME_TREX_X_POSITION 100
#define REX_GAME_TREX_Y_POSITION 472
#define REX_GAME_TREX_DUCK_Y_POSITION_OFFSET 34

/* horizon */
#define REX_GAME_HORIZON_X_POSITION 0
#define REX_GAME_HORIZON_Y_POSITION 540

/* cactus */
#define REX_GAME_CACTUS_SMALL_Y_POSITION 496
#define REX_GAME_CACTUS_LARGE_Y_POSITION 466

/* pterodactyl */
#define REX_GAME_PTERODACTYL_Y_POSITION_1 350
#define REX_GAME_PTERODACTYL_Y_POSITION_2 420
#define REX_GAME_PTERODACTYL_Y_POSITION_3 490

/* cloud */
#define REX_GAME_CLOUD_MAX_Y_POSITION 400
#define REX_GAME_CLOUD_MIN_Y_POSITION 300

/* score */
#define REX_GAME_MAX_SCORE 99999
#define REX_GAME_SCORE_INCREASE_COEFFICIENT 10 /* increasing this value will slow down the score add-up speed */
#define REX_GAME_SCORE_DIGIT_WIDTH 5
#define REX_GAME_HI_SCORE_X_POSITION 1400
#define REX_GAME_HI_SCORE_Y_POSITION 280
#define REX_GAME_CURRENT_SCORE_X_POSITION 1700
#define REX_GAME_CURRENT_SCORE_Y_POSITION 280

#define REX_GAME_FALL_BETWEEN_TREX_HORIZON 68
#define REX_GAME_OBJECT_CACTUS_Y_POSITION 480

/*============================== objects image ==============================*/
/* cloud */
#define IMAGE_CLOUD_ID 0
#define IMAGE_CLOUD_PATH "assets/cloud.png"
#define IMAGE_CLOUD_WIDTH 92
#define IMAGE_CLOUD_HEIGHT 27

/* horizon */
/* x: 2, y: 104 */
#define IMAGE_HORIZON_ID 1
#define IMAGE_HORIZON_PATH "assets/horizon.png"
#define IMAGE_HORIZON_WIDTH 2400
#define IMAGE_HORIZON_HEIGHT 24

/* moon */
#define MOON_X 954
#define MOON_Y 2

/* pterodactyl 0 */
/* x: 260, y: 14 */
#define IMAGE_PTERODACTYL_0_ID 2
#define IMAGE_PTERODACTYL_0_PATH "assets/pterodactyl_0.png"
#define IMAGE_PTERODACTYL_0_WIDTH 92
#define IMAGE_PTERODACTYL_0_HEIGHT 80

/* pterodactyl 1 */
/* x: */
#define IMAGE_PTERODACTYL_1_ID 3
#define IMAGE_PTERODACTYL_1_PATH "assets/pterodactyl_1.png"
#define IMAGE_PTERODACTYL_1_WIDTH 92
#define IMAGE_PTERODACTYL_1_HEIGHT 80

/* game over text */
/* x: 1294, y: 29 */
#define IMAGE_GAME_OVER_TEXT_ID 4
#define IMAGE_GAME_OVER_TEXT_PATH "assets/game_over_text.png"
#define IMAGE_GAME_OVER_TEXT_WIDTH 381
#define IMAGE_GAME_OVER_TEXT_HEIGHT 21

/* restart */
/* x: 2, y: 2 */
#define IMAGE_RESTART_ID 5
#define IMAGE_RESTART_PATH "assets/restart.png"
#define IMAGE_RESTART_WIDTH 36
#define IMAGE_RESTART_HEIGHT 32

/* text sprite */
/* x: 1294, y: 2 */
#define IMAGE_TEXT_SPRITE_ID 6
#define IMAGE_TEXT_SPRITE_PATH "assets/text_sprite.png"
#define IMAGE_TEXT_SPRITE_WIDTH 238
#define IMAGE_TEXT_SPRITE_HEIGHT 21
#define IMAGE_TEXT_SPRITE_DIGIT_WIDTH 18
#define IMAGE_TEXT_SPRITE_DIGIT_OFFSET 20

/* trex 0 */
/* x: 0, y: 58 */
#define IMAGE_TREX_0_ID 7
#define IMAGE_TREX_0_PATH "assets/trex_0.png"
#define IMAGE_TREX_0_WIDTH 128
#define IMAGE_TREX_0_HEIGHT 86

/* trex 2 */
/* x: 1678, y: 2 */
#define IMAGE_TREX_2_ID 8
#define IMAGE_TREX_2_PATH "assets/trex_2.png"
#define IMAGE_TREX_2_WIDTH 300
#define IMAGE_TREX_2_HEIGHT 94

/* trex 4 */
/* x: 1678 + 44 * 2 * 2, y: 2 */
#define IMAGE_TREX_4_ID 9
#define IMAGE_TREX_4_PATH "assets/trex_4.png"
#define IMAGE_TREX_4_WIDTH 88
#define IMAGE_TREX_4_HEIGHT 94

/* trex 5 */
/* x: 1678 + 44 * 3 * 2, y: 2 */
#define IMAGE_TREX_5_ID 10
#define IMAGE_TREX_5_PATH "assets/trex_5.png"
#define IMAGE_TREX_5_WIDTH 88
#define IMAGE_TREX_5_HEIGHT 94

/* trex 6 */
/* x: 1678 + 44 * 4 * 2, y: 2 */
#define IMAGE_TREX_6_ID 11
#define IMAGE_TREX_6_PATH "assets/trex_6.png"
#define IMAGE_TREX_6_WIDTH 88
#define IMAGE_TREX_6_HEIGHT 94

/* trex 7 */
/* x: 1678 + 44 * 5 * 2 + 4, y: 2 + 4 */
#define IMAGE_TREX_7_ID 12
#define IMAGE_TREX_7_PATH "assets/trex_7.png"
#define IMAGE_TREX_7_WIDTH 80
#define IMAGE_TREX_7_HEIGHT 86

/* trex 8 */
/* x: 2203, y: 36 */
#define IMAGE_TREX_8_ID 13
#define IMAGE_TREX_8_PATH "assets/trex_8.png"
#define IMAGE_TREX_8_WIDTH 118
#define IMAGE_TREX_8_HEIGHT 60

/* trex 9 */
/* x: 2321, y: 36 */
#define IMAGE_TREX_9_ID 14
#define IMAGE_TREX_9_PATH "assets/trex_9.png"
#define IMAGE_TREX_9_WIDTH 118
#define IMAGE_TREX_9_HEIGHT 60

/* cactus small 0 */
/* x: 446, y: 2 */
#define IMAGE_CACTUS_SMALL_0_ID 15
#define IMAGE_CACTUS_SMALL_0_PATH "assets/cactus_small_0.png"
#define IMAGE_CACTUS_SMALL_0_WIDTH 34
#define IMAGE_CACTUS_SMALL_0_HEIGHT 70

/* cactus small 1 */
/* x: 480, y: 2 */
#define IMAGE_CACTUS_SMALL_1_ID 16
#define IMAGE_CACTUS_SMALL_1_PATH "assets/cactus_small_1.png"
#define IMAGE_CACTUS_SMALL_1_WIDTH 68
#define IMAGE_CACTUS_SMALL_1_HEIGHT 70

/* cactus small 2 */
/* x: 548, y: 2 */
#define IMAGE_CACTUS_SMALL_2_ID 17
#define IMAGE_CACTUS_SMALL_2_PATH "assets/cactus_small_2.png"
#define IMAGE_CACTUS_SMALL_2_WIDTH 102
#define IMAGE_CACTUS_SMALL_2_HEIGHT 70

/* cactus large 0 */
/* x: 652, y: 2 */
#define IMAGE_CACTUS_LARGE_0_ID 18
#define IMAGE_CACTUS_LARGE_0_PATH "assets/cactus_large_0.png"
#define IMAGE_CACTUS_LARGE_0_WIDTH 50
#define IMAGE_CACTUS_LARGE_0_HEIGHT 100

/* cactus large 1 */
/* x: 702, y: 2 */
#define IMAGE_CACTUS_LARGE_1_ID 19
#define IMAGE_CACTUS_LARGE_1_PATH "assets/cactus_large_1.png"
#define IMAGE_CACTUS_LARGE_1_WIDTH 100
#define IMAGE_CACTUS_LARGE_1_HEIGHT 100

/* cactus large 2 */
/* x: 802, y: 2 */
#define IMAGE_CACTUS_LARGE_2_ID 20
#define IMAGE_CACTUS_LARGE_2_PATH "assets/cactus_large_2.png"
#define IMAGE_CACTUS_LARGE_2_WIDTH 150
#define IMAGE_CACTUS_LARGE_2_HEIGHT 100

/* star */
#define STAR_X 1276
#define STAR_Y 2

/*==============================sound=====================================*/
#define SOUND_AMOUNT 3
/* hit */
#define SOUND_HIT_ID 0
#define SOUND_HIT_PATH "sounds/hit.ogg"

/* press */
#define SOUND_PRESS_ID 1
#define SOUND_PRESS_PATH "sounds/press.ogg"

/* reached */
#define SOUND_REACHED_ID 2
#define SOUND_REACHED_PATH "sounds/reached.ogg"

/*============================== all scenes ==============================*/
/* define scenes name */
#define BEGIN_SCENE_NAME "Begin Scene"
#define MAIN_SCENE_NAME "Main Scene"
#define END_SCENE_NAME "End Scene"

/* begin scene */
#define BEGIN_SCENE_FALL_BETWEEN_TREX_HORIZON REX_GAME_FALL_BETWEEN_TREX_HORIZON
#define BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH IMAGE_TREX_2_WIDTH
#define BEGIN_SCENE_PROMT_TEXT_WIDTH 700
#define BEGIN_SCENE_PROMT_TEXT_HEIGHT 50 /* match the height of fonts[0] */
#define BEGIN_SCENE_PROMT_TEXT_X 610
#define BEGIN_SCENE_PROMT_TEXT_Y 450
#define BEGIN_SCENE_PROMT_TEXT_ROW_HEIGHT 30
#define BEGIN_SCENE_TREX_X REX_GAME_TREX_X_POSITION
#define BEGIN_SCENE_TREX_Y REX_GAME_TREX_Y_POSITION
#define BEGIN_SCENE_HORIZON_X REX_GAME_HORIZON_X_POSITION
#define BEGIN_SCENE_HORIZON_Y REX_GAME_HORIZON_Y_POSITION

/* main scene */
#define MAIN_SCENE_FALL_BETWEEN_TREX_HORIZON REX_GAME_FALL_BETWEEN_TREX_HORIZON
#define MAIN_SCENE_TREX_X REX_GAME_TREX_X_POSITION
#define MAIN_SCENE_TREX_Y REX_GAME_TREX_Y_POSITION
#define MAIN_SCENE_HORIZON_X REX_GAME_HORIZON_X_POSITION
#define MAIN_SCENE_HORIZON_Y REX_GAME_HORIZON_Y_POSITION
#define MAIN_SCENE_HI_SCORE_X REX_GAME_HI_SCORE_X_POSITION
#define MAIN_SCENE_HI_SCORE_Y REX_GAME_HI_SCORE_Y_POSITION
#define MAIN_SCENE_CURRENT_SCORE_X REX_GAME_CURRENT_SCORE_X_POSITION
#define MAIN_SCENE_CURRENT_SCORE_Y REX_GAME_CURRENT_SCORE_Y_POSITION

/* end scene */
#define END_SCENE_FALL_BETWEEN_TREX_HORIZON REX_GAME_FALL_BETWEEN_TREX_HORIZON
#define END_SCENE_TREX_X REX_GAME_TREX_X_POSITION
#define END_SCENE_TREX_Y REX_GAME_TREX_Y_POSITION
#define END_SCENE_TREX_DUCK_TO_DEAD_SHRINK 34
#define END_SCENE_GAP_BETWEEN_HI_SCORE 20
#define END_SCENE_HORIZON_X REX_GAME_HORIZON_X_POSITION
#define END_SCENE_HORIZON_Y REX_GAME_HORIZON_Y_POSITION
#define END_SCENE_RESTART_X 924
#define END_SCENE_RESTART_Y 430
#define END_SCENE_GAME_OVER_X 769.5f
#define END_SCENE_GAME_OVER_Y 350
#define END_SCENE_HI_SCORE_X REX_GAME_HI_SCORE_X_POSITION
#define END_SCENE_HI_SCORE_Y REX_GAME_HI_SCORE_Y_POSITION
#define END_SCENE_CURRENT_SCORE_X REX_GAME_CURRENT_SCORE_X_POSITION
#define END_SCENE_CURRENT_SCORE_Y REX_GAME_CURRENT_SCORE_Y_POSITION

/* global varible */
static unsigned int rex_random_seed;        /* global random seed */
static unsigned char rex_refresh_cycle = 0; /* refresh cycle */
static unsigned int rex_frame = 0;          /* frames */
static nk_bool rex_scene_lock = nk_false;   /* not switch scene when lock */

static float rex_game_speed = REX_GAME_SPEED;
static unsigned int rex_hi_score = 0;
static unsigned int rex_current_score = 0;

static cs_context_t *rex_sound_ctx;                    /* sound context */
static cs_loaded_sound_t rex_sounds_buf[SOUND_AMOUNT]; /* sounds in memory */
static cs_play_sound_def_t rex_sounds[SOUND_AMOUNT];   /* sounds definition */

static const char rex_sound_path_list[SOUND_AMOUNT][MAX_PATH_LENGTH] = {
    SOUND_HIT_PATH,
    SOUND_PRESS_PATH,
    SOUND_REACHED_PATH};

static const char rex_image_path_list[MAX_IMAGES_AMOUNT][MAX_PATH_LENGTH] = {
    IMAGE_CLOUD_PATH,
    IMAGE_HORIZON_PATH,
    IMAGE_PTERODACTYL_0_PATH,
    IMAGE_PTERODACTYL_1_PATH,
    IMAGE_GAME_OVER_TEXT_PATH,
    IMAGE_RESTART_PATH,
    IMAGE_TEXT_SPRITE_PATH,
    IMAGE_TREX_0_PATH,
    IMAGE_TREX_2_PATH,
    IMAGE_TREX_4_PATH,
    IMAGE_TREX_5_PATH,
    IMAGE_TREX_6_PATH,
    IMAGE_TREX_7_PATH,
    IMAGE_TREX_8_PATH,
    IMAGE_TREX_9_PATH,
    IMAGE_CACTUS_SMALL_0_PATH,
    IMAGE_CACTUS_SMALL_1_PATH,
    IMAGE_CACTUS_SMALL_2_PATH,
    IMAGE_CACTUS_LARGE_0_PATH,
    IMAGE_CACTUS_LARGE_1_PATH,
    IMAGE_CACTUS_LARGE_2_PATH};

#endif
