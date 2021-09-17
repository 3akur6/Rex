/* won't change status if trex object in queue */
void rex_game_init_trex(void)
{
    /* place trex object in array[0] */
    struct rex_game_object *trex = &rex_objects[0];
    /* trex is already in rex_objects */
    if (trex->type == REX_GAME_OBJECT_TREX)
        return;

    int need_frames_amount_one_way = (int)sqrt((2 * REX_GAME_JUMP_HEIGHT) / REX_GAME_GRAVITY);
    int need_frames_amount = 2 * need_frames_amount_one_way;
    float rex_jump_initial_velocity = REX_GAME_GRAVITY * need_frames_amount_one_way;

    /* trex hasn't been added to rex_objects */
    struct rex_image image;
    image = rex_image_load(IMAGE_TREX_2_ID);

    trex->active = nk_true;
    trex->type = REX_GAME_OBJECT_TREX;
    trex->width = image.width;
    trex->height = image.height;

    trex->x = REX_GAME_TREX_X_POSITION;
    trex->y = REX_GAME_TREX_Y_POSITION;

    trex->detail.trex = REX_GAME_TREX_STATIC; /* default value */
}

struct rex_game_object *rex_object_get_trex(void)
{
    return &rex_objects[0];
}

void rex_game_set_trex_status(enum rex_game_trex_type trex_status)
{
    rex_objects[0].detail.trex = trex_status;
}

void rex_object_trex_walk(struct nk_context *ctx, struct rex_game_object *trex)
{
    /* reset (x,y) */
    trex->x = REX_GAME_TREX_X_POSITION;
    trex->y = REX_GAME_TREX_Y_POSITION;

    if (rex_frame & REX_GAME_TREX_WALK_SPEED)
        rex_draw_image(ctx, IMAGE_TREX_4_ID, trex->x, trex->y);
    else
        rex_draw_image(ctx, IMAGE_TREX_5_ID, trex->x, trex->y);

    return;
}

void rex_object_trex_jump(struct nk_context *ctx, struct rex_game_object *trex)
{
    int need_frames_amount_one_way = (int)sqrt((2 * REX_GAME_JUMP_HEIGHT) / REX_GAME_GRAVITY);
    int need_frames_amount = 2 * need_frames_amount_one_way;
    float rex_jump_initial_velocity = REX_GAME_GRAVITY * need_frames_amount_one_way;

    int destroy = trex->destroy_at_frame;
    int create = trex->create_at_frame;

    float delta_frame;
    int frame_over_one_way;
    float y_upthrow_offset;
    float y_drop_offset;

    float offset_y;

    if (trex->detail.trex == REX_GAME_TREX_JUMP && (rex_frame <= destroy && rex_frame >= create) && create < destroy)
    { /* jump */
        /* |-----|create|--------|mid|------|destroy|---| */
        delta_frame = rex_frame - create;
        frame_over_one_way = delta_frame - need_frames_amount_one_way;
        y_upthrow_offset = rex_jump_initial_velocity * delta_frame - (REX_GAME_GRAVITY * delta_frame * delta_frame) / 2;
        y_drop_offset = REX_GAME_JUMP_HEIGHT - REX_GAME_GRAVITY * frame_over_one_way * frame_over_one_way / 2;

        int mid = (create + destroy) / 2;
        if (rex_frame > create && rex_frame <= mid)
            offset_y = y_upthrow_offset;
        else if (rex_frame < destroy && rex_frame > mid)
            offset_y = y_drop_offset;
        else if (rex_frame == destroy)
        {                          /* finish jumping */
            trex->detail.trex = 0; /* set to meaningless status */
            rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
            return;
        }
        trex->y = REX_GAME_TREX_Y_POSITION - offset_y;
        rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
    }
    else if (trex->detail.trex == REX_GAME_TREX_JUMP && (rex_frame <= destroy || rex_frame >= create) && create > destroy)
    { /* jump */
        /* |------|destroy|-------|create|-------*/
        if (rex_frame >= create)
            delta_frame = rex_frame - create;
        else
            delta_frame = MAX_FRAME_AMOUNT - create + rex_frame;

        frame_over_one_way = delta_frame - need_frames_amount_one_way;
        y_upthrow_offset = rex_jump_initial_velocity * delta_frame - (REX_GAME_GRAVITY * delta_frame * delta_frame) / 2;
        y_drop_offset = REX_GAME_JUMP_HEIGHT - REX_GAME_GRAVITY * frame_over_one_way * frame_over_one_way / 2;

        int half = (MAX_FRAME_AMOUNT - create + destroy) / 2;
        if (half < MAX_FRAME_AMOUNT - create)
        { /* |-----|destroy|---------|create|-----|mid|---| */
            int mid = half + create;
            if (rex_frame >= create && rex_frame <= mid)
                offset_y = y_upthrow_offset;
            else if (rex_frame > mid || rex_frame < destroy)
                offset_y = y_drop_offset;
            else if (rex_frame == destroy)
            {
                trex->detail.trex = 0; /* set to meaningless status */
                rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
                return;
            }
        }
        else
        { /* |--|mid|------|destroy|---------|create|----| */
            int mid = destroy - half;
            if (rex_frame >= create || rex_frame <= mid)
                offset_y = y_upthrow_offset;
            else if (rex_frame > mid && rex_frame < destroy)
                offset_y = y_drop_offset;
            else if (rex_frame == destroy)
            {
                trex->detail.trex = 0; /* set to meaningless status */
                rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
                return;
            }
        }
        trex->y = REX_GAME_TREX_Y_POSITION - offset_y;
        rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
    }
    else
    { /* set jump */
        trex->detail.trex = REX_GAME_TREX_JUMP;
        trex->x = REX_GAME_TREX_X_POSITION;
        trex->y = REX_GAME_TREX_Y_POSITION;
        trex->create_at_frame = (rex_frame + 1) % MAX_FRAME_AMOUNT;                               /* create jump next frame */
        trex->destroy_at_frame = (trex->create_at_frame + need_frames_amount) % MAX_FRAME_AMOUNT; /* set destroy frame */

        rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
    }
}

void rex_game_draw_trex(struct nk_context *ctx, struct rex_game_object *trex)
{
    float place_x = trex->x;
    float place_y = trex->y;

    switch (trex->detail.trex)
    {
    case REX_GAME_TREX_STATIC:
        rex_draw_image(ctx, IMAGE_TREX_2_ID, trex->x, trex->y);
        break;
    case REX_GAME_TREX_JUMP:
        rex_object_trex_jump(ctx, trex);
        break;
    case REX_GAME_TREX_DUCK:
        break;
    case REX_GAME_TREX_WALK:
        rex_object_trex_walk(ctx, trex);
        break;
    default:
        rex_object_trex_walk(ctx, trex);
    }
}
