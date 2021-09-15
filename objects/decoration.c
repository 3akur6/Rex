#include "horizon.c"

void rex_object_cloud_float(struct nk_context *ctx, struct rex_game_object *cloud)
{
    int create = cloud->create_at_frame;
    int destroy = cloud->destroy_at_frame;
    float offset_x = 0;
    int delta_frame;

    if (create < destroy)
    { /* |-----|create|--------------|destroy|---| */
        if (rex_frame >= create && rex_frame < destroy)
            delta_frame = rex_frame - create;
        else if (rex_frame == destroy)
        { /* disable */
            cloud->active = nk_false;
            return;
        }
    }
    else
    { /* destroy < create */
        if (rex_frame > create)
        { /* |-----|destroy|---------|create|--|rex_frame|--| */
            delta_frame = rex_frame - create;
        }
        else if (rex_frame < destroy)
        { /* |-|rex_frame|----|destroy|---------|create|----| */
            delta_frame = MAX_FRAME_AMOUNT - create + rex_frame;
        }
        else if (rex_frame == destroy)
        { /* disable */
            cloud->active = nk_false;
            return;
        }
    }
    offset_x = delta_frame * REX_GAME_CLOUD_SPEED; /* factor should be macro */

    cloud->x -= offset_x;
}

void rex_game_draw_decoration(struct nk_context *ctx, struct rex_game_object *decoration)
{
    switch (decoration->detail.decoration)
    {
    case REX_GAME_DECORATION_CLOUD:
        rex_object_cloud_float(ctx, decoration);
        break;
    }
}