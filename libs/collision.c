#define MAX_BOX_AMOUNT 10

struct collision_box
{
    float x;
    float y;
    unsigned int width;
    unsigned int height;
};

void collision_debug_print_collision_box(struct collision_box *box, char *msg)
{
    printf("[collision_debug_print_collision_box (%s) (%d)] ", msg, rex_current_score);
    printf("(x,y)->(%f,%f), width->%u, height->%u\n", box->x, box->y, box->width, box->height);
}

nk_bool collision_detect(struct collision_box *box1, struct collision_box *box2)
{
    unsigned int box1_x = box1->x;
    unsigned int box1_x_right = box1->x + box1->width;
    unsigned int box1_y = box1->y;
    unsigned int box1_y_bottom = box1->y + box1->height;

    unsigned int box2_x = box2->x;
    unsigned int box2_x_right = box2->x + box2->width;
    unsigned int box2_y = box2->y;
    unsigned int box2_y_bottom = box2->y + box2->height;

    if (box1_x_right < box2_x || box1_x > box2_x_right || box1_y_bottom < box2_y || box1_y > box2_y_bottom)
        /* no collision */
        return nk_false;

    return nk_true;
}

struct rex_collision_collection
{
    unsigned char amount; /* boxes amount */
    struct collision_box boxes[MAX_BOX_AMOUNT];
};

void rex_game_trex_get_collision_collection(struct rex_game_object *trex, struct rex_collision_collection *collection)
{
    collection->amount = 1;

    struct collision_box box;
    box.x = trex->x;
    box.y = trex->y;
    box.width = trex->width;
    box.height = trex->height;

    collection->boxes[0] = box;
}

void rex_game_obstacle_get_collision_collection(struct rex_game_object *obstacle, struct rex_collision_collection *collection)
{
    collection->amount = 1;

    struct collision_box box;
    box.x = obstacle->x;
    box.y = obstacle->y;
    box.width = obstacle->width;
    box.height = obstacle->height;

    // switch (obstacle->detail.obstacle)
    // {
    // case REX_GAME_OBSTACLE_PTERODACTYL:
    // {
    //     box.width = trex;
    //     break;
    // }
    // case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
    // {
    //     break;
    // }
    // case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
    // {
    //     break;
    // }
    // case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
    // {
    //     break;
    // }
    // case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
    // {
    //     break;
    // }
    // case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
    // {
    //     break;
    // }
    // case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
    // {
    //     break;
    // }
    // }

    collection->boxes[0] = box;
}

void rex_game_object_get_collison_collection(struct rex_game_object *object, struct rex_collision_collection *collection)
{
    switch (object->type)
    { /* ignore decoration object */
    case REX_GAME_OBJECT_TREX:
        rex_game_trex_get_collision_collection(object, collection);
        break;
    case REX_GAME_OBJECT_OBSTACLE:
        rex_game_obstacle_get_collision_collection(object, collection);
        break;
    }
}

/* shouldn't call this function in other place */
nk_bool _rex_game_collision_detect(struct rex_game_object *object1, struct rex_game_object *object2)
{
    struct rex_collision_collection collection1;
    struct rex_collision_collection collection2;

    rex_game_object_get_collison_collection(object1, &collection1);
    rex_game_object_get_collison_collection(object2, &collection2);

    for (unsigned char i = 0; i < collection1.amount; i++)
    { /* iterate collection1 boxes */
        for (unsigned char j = 0; j < collection2.amount; j++)
        { /* iterate collection2 boxes */
            if (collision_detect(&collection1.boxes[i], &collection2.boxes[j]) == nk_true)
            {
                printf("[_rex_game_collision_detect] collision detected\n");
                return nk_true;
            }
        }
    }

    return nk_false;
}

nk_bool rex_game_collision_detect(void)
{
    struct rex_game_object *object1 = rex_game_get_closest_obstacle();
    struct rex_game_object *object2 = rex_object_get_trex();

    if (object1 != NULL && object2 != NULL)
        return _rex_game_collision_detect(object1, object2);

    return nk_false;
}
