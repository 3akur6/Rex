#ifndef UI_H_
#define UI_H_

/* refresh after draw cycles */
#define REFRESH_CYCLES 1
#define MAX_FRAME_AMOUNT 255

/* max buffer size of images */
#define MAX_IMAGES_AMOUNT 20

/* max buffer size of path name */
#define MAX_PATH_LENGTH 50

/* predefine window width and height */
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

/* game settings */
#define REX_GAME_GRAVITY 0.6
#define REX_GAME_JUMP_HEIGHT 140
#define REX_GAME_JUMP_STEP 2
#define REX_GAME_SPEED 1

/*============================== objects image ==============================*/
/* cactus large */
#define CACTUS_LARGE_X 652
#define CACTUS_LARGE_Y 2

/* cactus small */
#define CACTUS_SMALL_X 446
#define CACTUS_SMALL_Y 2

/* cloud */
#define IMAGE_CLOUD_ID 0
#define IMAGE_CLOUD_PATH "assets/cloud.png"
#define IMAGE_CLOUD_WIDTH 96
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

/* pterodactyl */
#define PTERODACTYL_X 260
#define PTERODACTYL_Y 2

/* game over text */
/* x: 1294, y: 29 */
#define IMAGE_GAME_OVER_TEXT_ID 2
#define IMAGE_GAME_OVER_TEXT_PATH "assets/game_over_text.png"
#define IMAGE_GAME_OVER_TEXT_WIDTH 381
#define IMAGE_GAME_OVER_TEXT_HEIGHT 21

/* restart */
/* x: 2, y: 2 */
#define IMAGE_RESTART_ID 3
#define IMAGE_RESTART_PATH "assets/restart.png"
#define IMAGE_RESTART_WIDTH 36
#define IMAGE_RESTART_HEIGHT 32

/* text sprite */
/* x: 1294, y: 2 */
#define IMAGE_TEXT_SPRITE_ID 4
#define IMAGE_TEXT_SPRITE_PATH "assets/text_sprite.png"
#define IMAGE_TEXT_SPRITE_WIDTH 238
#define IMAGE_TEXT_SPRITE_HEIGHT 21
#define IMAGE_TEXT_SPRITE_DIGIT_WIDTH 18
#define IMAGE_TEXT_SPRITE_DIGIT_OFFSET 20

/* trex 0 */
/* x: 0, y: 58 */
#define IMAGE_TREX_0_ID 5
#define IMAGE_TREX_0_PATH "assets/trex_0.png"
#define IMAGE_TREX_0_WIDTH 128
#define IMAGE_TREX_0_HEIGHT 86

/* trex 2 */
/* x: 1678, y: 2 */
#define IMAGE_TREX_2_ID 6
#define IMAGE_TREX_2_PATH "assets/trex_2.png"
#define IMAGE_TREX_2_WIDTH 88
#define IMAGE_TREX_2_HEIGHT 94

/* trex 4 */
/* x: 1678 + 44 * 2 * 2, y: 2 */
#define IMAGE_TREX_4_ID 7
#define IMAGE_TREX_4_PATH "assets/trex_4.png"
#define IMAGE_TREX_4_WIDTH 88
#define IMAGE_TREX_4_HEIGHT 94

/* trex 5 */
/* x: 1678 + 44 * 3 * 2, y: 2 */
#define IMAGE_TREX_5_ID 8
#define IMAGE_TREX_5_PATH "assets/trex_5.png"
#define IMAGE_TREX_5_WIDTH 88
#define IMAGE_TREX_5_HEIGHT 94

/* trex 6 */
/* x: 1678 + 44 * 4 * 2, y: 2 */
#define IMAGE_TREX_6_ID 9
#define IMAGE_TREX_6_PATH "assets/trex_6.png"
#define IMAGE_TREX_6_WIDTH 88
#define IMAGE_TREX_6_HEIGHT 94

/* trex 7 */
/* x: 1678 + 44 * 5 * 2 + 4, y: 2 + 4 */
#define IMAGE_TREX_7_ID 10
#define IMAGE_TREX_7_PATH "assets/trex_7.png"
#define IMAGE_TREX_7_WIDTH 80
#define IMAGE_TREX_7_HEIGHT 86

/* star */
#define STAR_X 1276
#define STAR_Y 2

/*============================== all scenes ==============================*/
/* define scenes name */
#define BEGIN_SCENE_NAME "Begin Scene"
#define MAIN_SCENE_NAME "Main Scene"
#define END_SCENE_NAME "End Scene"

/* begin scene */
#define BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH IMAGE_TREX_2_WIDTH

/* main scene */

/* end scene */
#define END_SCENE_GAP_BETWEEN_HI_SCORE 20
#define END_SCENE_FALL_BETWEEN_TREX_HORIZON 68

/* global varible */
static unsigned char rex_refresh_cycle = 0; /* refresh cycle */
static unsigned char rex_frame = 0;         /* frames */
static nk_bool rex_event_lock = nk_false;   /* not handle event when lock */

static unsigned char rex_game_speed = REX_GAME_SPEED;
static unsigned int rex_hi_score = 99999;
static unsigned int rex_current_score = 0;
static unsigned int rex_horizon_line_offset = 0;

static const char rex_image_path_list[MAX_IMAGES_AMOUNT][MAX_PATH_LENGTH] = {
    IMAGE_CLOUD_PATH,
    IMAGE_HORIZON_PATH,
    IMAGE_GAME_OVER_TEXT_PATH,
    IMAGE_RESTART_PATH,
    IMAGE_TEXT_SPRITE_PATH,
    IMAGE_TREX_0_PATH,
    IMAGE_TREX_2_PATH,
    IMAGE_TREX_4_PATH,
    IMAGE_TREX_5_PATH,
    IMAGE_TREX_6_PATH,
    IMAGE_TREX_7_PATH};

#endif