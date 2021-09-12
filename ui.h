#ifndef UI_H_
#define UI_H_

/* refresh after draw cycles */
#define REFRESH_CYCLES 1

/* predefine window width and height */
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

/* game settings */
#define REX_JUMP_HEIGHT 140
#define REX_JUMP_STEP 2

/*============================== objects image ==============================*/
/* objects image path */
#define OBJECTS_IMAGE_PATH "assets/200-offline-sprite1.png"

/* cactus large */
#define CACTUS_LARGE_X 652
#define CACTUS_LARGE_Y 2

/* cactus small */
#define CACTUS_SMALL_X 446
#define CACTUS_SMALL_Y 2

/* cloud */
#define CLOUD_X 166
#define CLOUD_Y 2

/* horizon */
/* x: 2, y: 104 */
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
#define IMAGE_GAME_OVER_TEXT_PATH "assets/game_over_text.png"
#define IMAGE_GAME_OVER_TEXT_WIDTH 381
#define IMAGE_GAME_OVER_TEXT_HEIGHT 21

/* restart */
/* x: 2, y: 2 */
#define IMAGE_RESTART_PATH "assets/restart.png"
#define IMAGE_RESTART_WIDTH 36
#define IMAGE_RESTART_HEIGHT 32

/* text sprite */
/* x: 1294, y: 2 */
#define IMAGE_TEXT_SPRITE_PATH "assets/text_sprite.png"
#define IMAGE_TEXT_SPRITE_WIDTH 238
#define IMAGE_TEXT_SPRITE_HEIGHT 21
#define IMAGE_TEXT_SPRITE_DIGIT_WIDTH 18
#define IMAGE_TEXT_SPRITE_DIGIT_OFFSET 20

/* trex 2 */
/* x: 1678, y: 2 */
#define IMAGE_TREX_2_PATH "assets/trex_2.png"
#define IMAGE_TREX_2_WIDTH 88
#define IMAGE_TREX_2_HEIGHT 94

/* trex 4 */
/* x: 1678 + 44 * 2 * 2, y: 2 */
#define IMAGE_TREX_4_PATH "assets/trex_4.png"
#define IMAGE_TREX_4_WIDTH 88
#define IMAGE_TREX_4_HEIGHT 94

/* trex 5 */
/* x: 1678 + 44 * 3 * 2, y: 2 */
#define IMAGE_TREX_5_PATH "assets/trex_5.png"
#define IMAGE_TREX_5_WIDTH 88
#define IMAGE_TREX_5_HEIGHT 94

/* trex 6 */
/* x: 1678 + 44 * 4 * 2, y: 2 */
#define IMAGE_TREX_6_PATH "assets/trex_6.png"
#define IMAGE_TREX_6_WIDTH 88
#define IMAGE_TREX_6_HEIGHT 94

/* trex 7 */
/* x: 1678 + 44 * 5 * 2 + 4, y: 2 + 4 */
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
#define BEGIN_SCENE_REX_STATIC_IMAGE_PATH "assets/200-error-offline.png"
#define BEGIN_SCENE_FIRST_JUMP_HOIZON_WIDTH IMAGE_TREX_2_WIDTH

/* main scene */

/* end scene */
#define END_SCENE_GAP_BETWEEN_HI_SCORE 20
#define END_SCENE_FALL_BETWEEN_TREX_HORIZON 68

/* global varible */
static unsigned char rex_refresh_cycle = 0; /* refresh cycle */
static unsigned char rex_frame = 0;         /* frames */
static nk_bool rex_event_lock = nk_false;   /* not handle event when lock */
static unsigned int rex_hi_score = 99999;
static unsigned int rex_current_score = 0;

#endif