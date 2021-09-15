#include "utilities.h"

struct rex_image
{
    int width;
    int height;
    struct nk_image handle;
};

static nk_bool rex_image_cached_list[MAX_IMAGES_AMOUNT]; /* if rex_image_cached_list[image_id] is nk_true, this image has been cached in rex_images[image_id] */
struct rex_image rex_images[MAX_IMAGES_AMOUNT];          /* images buffer */

static struct rex_image rex_image_load(unsigned char image_id)
{
    /* image has been cached */
    if (rex_image_cached_list[image_id] == nk_true)
        return rex_images[image_id];

    struct rex_image image;
    int x, y, n;
    GLuint tex;

    unsigned char *data = stbi_load(rex_image_path_list[image_id], &x, &y, &n, 0);
    if (data == NULL)
        fprintf(stderr, "%s\n", stbi_failure_reason());

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA4, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    image.handle = nk_image_id((int)tex);
    image.width = x;
    image.height = y;

    rex_images[image_id] = image;
    rex_image_cached_list[image_id] = nk_true;

    return rex_images[image_id];
}

/* load part of image from file 
x, y: from (x, y) to cut off the subimage
sub_width: subimage width
sub_height: subimage height
*/
static struct rex_image rex_subimage_load(unsigned char image_id, float x, float y, float sub_width, float sub_height)
{
    struct rex_image whole = rex_image_load(image_id);

    struct nk_rect rect = nk_rect(x, y, sub_width, sub_height); /* rect to cut off the image */

    struct rex_image part;
    part.handle = nk_subimage_id(whole.handle.handle.id, whole.width, whole.height, rect);
    part.width = sub_width;
    part.height = sub_height;

    return part;
}

void rex_draw_image(struct nk_context *ctx, unsigned char image_id, float place_x, float place_y)
{
    struct nk_command_buffer *canvas;
    struct nk_rect rect;

    canvas = nk_window_get_canvas(ctx);

    struct rex_image image = rex_image_load(image_id);

    int image_width = image.width;
    int image_height = image.height;

    rect = nk_rect(place_x, place_y, image_width, image_height); /* create rect to draw image */
    nk_draw_image(canvas, rect, &image.handle, nk_white);
}

void rex_draw_subimage(struct nk_context *ctx, unsigned char image_id, float cut_x, float cut_y, float sub_width, float sub_height, float place_x, float place_y)
{
    struct nk_command_buffer *canvas;
    struct nk_rect rect;

    canvas = nk_window_get_canvas(ctx);

    struct rex_image image = rex_subimage_load(image_id, cut_x, cut_y, sub_width, sub_height);

    int image_width = image.width;
    int image_height = image.height;

    rect = nk_rect(place_x, place_y, image_width, image_height); /* create rect to draw image */
    nk_draw_image(canvas, rect, &image.handle, nk_white);
}

enum rex_key_status
{
    REX_KEY_PRESS,      /* press then release */
    REX_KEY_LONG_PRESS, /* long press */
    REX_KEY_RELEASE,    /* not press */
    REX_KEY_HOLD        /* keep pressing key for some time */
};

static unsigned int rex_space_press_since_release_times = 0; /* reset when space is released */

enum rex_key_status rex_get_space_status(void)
{ /* only check status when space is released */
    /* check raw space press status */
    unsigned int rex_space_press_since_release_times_saved = rex_space_press_since_release_times;

    if (glfwGetKey(glfw.win, GLFW_KEY_SPACE) == GLFW_PRESS)
        rex_space_press_since_release_times++;
    else
        rex_space_press_since_release_times = 0;

    /* space released */
    if (rex_space_press_since_release_times_saved == 0)
        return REX_KEY_RELEASE;

    /* still press */
    else if (rex_space_press_since_release_times >= KEY_HOLD_THRESHOLD)
        return REX_KEY_HOLD;

    /* space pressed */
    else if (rex_space_press_since_release_times_saved >= KEY_HOLD_THRESHOLD && rex_space_press_since_release_times == 0)
        return REX_KEY_LONG_PRESS;

    /* space hold */
    else /* if (rex_space_press_since_release_times > KEY_HOLD_THRESHOLD) */
        return REX_KEY_PRESS;
}

void rex_draw_digit(struct nk_context *ctx, unsigned char digit, float place_x, float place_y)
{
    /* only draw digits from 0 to 9 */
    if (digit < 0 && digit > 9)
        return;

    unsigned int offset = digit * IMAGE_TEXT_SPRITE_DIGIT_OFFSET;
    rex_draw_subimage(ctx, IMAGE_TEXT_SPRITE_ID, (float)offset, 0, IMAGE_TEXT_SPRITE_DIGIT_WIDTH, IMAGE_TEXT_SPRITE_HEIGHT, place_x, place_y);
}

void rex_draw_number(struct nk_context *ctx, unsigned int number, unsigned char digits_size, float place_x, float place_y)
{
    // if (number == 0)
    // {
    //     rex_draw_digit(ctx, number, place_x, place_y);
    //     return;
    // }
    /* store digits from low to high */
    unsigned char digits[MAX_DIGITS_AMOUNT];
    unsigned char digits_amount = 0;
    while (number > 0 || number % 10)
    {
        digits[digits_amount++] = number % 10;
        number /= 10;
    }
    /* now draw digit from high to low */
    float offset = 0;
    for (unsigned char i = 0; i < digits_size; i++)
    {
        unsigned char digit;
        if (i + 1 > digits_size - digits_amount)
            digit = digits[digits_amount - i - 1];
        else
            digit = 0; /* place 0 to blank position */
        rex_draw_digit(ctx, digit, place_x + offset, place_y);
        offset += DRAW_NUMBER_DIGIT_OFFSET;
    }
}

/* when refresh cycle reset, rex_refresh_lock is free */
nk_bool rex_refresh_lock_is_free(void)
{
    if (rex_refresh_cycle % REFRESH_CYCLES == 0)
        return nk_true;

    return nk_false;
}

/* introduce frames to draw dynamic image 
update refresh cycle and frame here
*/
void rex_begin_frames(void)
{
    rex_refresh_cycle++;
    rex_refresh_cycle %= REFRESH_CYCLES; /* refresh cycle between 0 and REFRESH_CYCLES */

    /* increase rex_frame when fininshing one refresh cycle */
    if (rex_refresh_cycle == 0)
        rex_frame = (rex_frame + 1) % MAX_FRAME_AMOUNT;
}

void rex_end_frames(void)
{
    rex_refresh_cycle = 0;
    rex_frame = 0;
}

void rex_ymove_image_from_to_gradually(struct nk_context *ctx, unsigned char image_id, float x, float from_y, float to_y, float step_y)
{
    float offset = from_y - to_y;
    int need_frames_amount = offset / step_y;

    /* increase rex_frame from 0 to REX_JUMP_HEIGHT then reset */
    if (rex_frame > need_frames_amount)
        rex_frame = 0;

    rex_draw_image(ctx, image_id, x, from_y - step_y * rex_frame);
}

// nk_bool rex_trex_jump(struct nk_context *ctx, unsigned char image_id, float x, float y)
// {
//     int need_frames_amount = (2 * REX_GAME_JUMP_HEIGHT) / REX_GAME_JUMP_STEP;
//     if (rex_frame > need_frames_amount)
//     {
//         rex_draw_image(ctx, image_id, x, y);
//         return nk_true;
//     }

//     if (rex_frame < (need_frames_amount / 2))
//         rex_draw_image(ctx, image_id, x, y - rex_frame * REX_GAME_JUMP_STEP);
//     else
//         rex_draw_image(ctx, image_id, x, y - REX_GAME_JUMP_HEIGHT + (rex_frame - need_frames_amount / 2) * REX_GAME_JUMP_STEP);

//     return nk_false;
// }

nk_bool rex_trex_jump(struct nk_context *ctx, unsigned char image_id, float x, float y)
{
    int need_frames_amount_one_way = (int)sqrt((2 * REX_GAME_JUMP_HEIGHT) / REX_GAME_GRAVITY);
    int need_frames_amount = 2 * need_frames_amount_one_way;
    float rex_jump_initial_velocity = REX_GAME_GRAVITY * need_frames_amount_one_way;
    //float rex_jump_initial_velocity = (REX_GAME_JUMP_HEIGHT + (REX_GAME_GRAVITY * need_frames_amount_one_way * need_frames_amount_one_way) / 2) / need_frames_amount_one_way;
    if (rex_frame > need_frames_amount)
    { /* draw static image */
        rex_draw_image(ctx, image_id, x, y);
        return nk_true;
    }

    if (rex_frame < need_frames_amount_one_way)
        rex_draw_image(ctx, image_id, x, y - (rex_jump_initial_velocity * rex_frame - (REX_GAME_GRAVITY * rex_frame * rex_frame) / 2));
    else
        rex_draw_image(ctx, image_id, x, y - REX_GAME_JUMP_HEIGHT + (REX_GAME_GRAVITY * (rex_frame - need_frames_amount_one_way) * (rex_frame - need_frames_amount_one_way)) / 2);

    return nk_false;
}

#include "../objects/objects.h"
#include "../objects/objects.c"
