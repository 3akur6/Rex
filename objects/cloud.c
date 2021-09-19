void rex_object_cloud_float(struct nk_context *ctx, struct rex_game_object *cloud)
{
    int create = cloud->create_at_frame;
    int destroy = cloud->destroy_at_frame;
    float offset_x = 0;

    if (create < destroy)
    { /* |-----|create|--------------|destroy|---| */
        if (rex_frame >= create && rex_frame < destroy)
            rex_draw_image(ctx, IMAGE_CLOUD_ID, cloud->x, cloud->y);
        else if (rex_frame == destroy)
        { /* disable */
            cloud->active = INACTIVE;
            return;
        }
    }
    else
    { /* destroy < create */
        if (rex_frame >= create || rex_frame < destroy)
        { /* |-----|destroy|---------|create|---| */
            rex_draw_image(ctx, IMAGE_CLOUD_ID, cloud->x, cloud->y);
        }
        else if (rex_frame == destroy)
        { /* disable */
            cloud->active = INACTIVE;
            return;
        }
    }
    offset_x = rex_game_speed * REX_GAME_CLOUD_SPEED; /* factor should be macro */

    cloud->x -= offset_x;
}
