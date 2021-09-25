nk_bool collision_detect(struct collision_box *box1, struct collision_box *box2)
{
    float box1_x = box1->x;
    float box1_x_right = box1->x + box1->width;
    float box1_y = box1->y;
    float box1_y_bottom = box1->y + box1->height;

    float box2_x = box2->x;
    float box2_x_right = box2->x + box2->width;
    float box2_y = box2->y;
    float box2_y_bottom = box2->y + box2->height;

    if (box1_x_right <= box2_x || box1_x >= box2_x_right || box1_y_bottom <= box2_y || box1_y >= box2_y_bottom)
        /* no collision */
        return nk_false;

    return nk_true;
}

struct rex_collision_collection *rex_game_trex_get_collision_collection(struct rex_game_object *trex)
{
    switch (trex->detail.trex)
    {
    case REX_GAME_TREX_STATIC:
    case REX_GAME_TREX_JUMP:
    case REX_GAME_TREX_WALK:
        return &rex_collision_collections[REX_TREX_WALK_COLLISION_COLLECTION_INDEX];
    case REX_GAME_TREX_DUCK:
        return &rex_collision_collections[REX_TREX_DUCK_COLLISION_COLLECTION_INDEX];
    }
}

struct rex_collision_collection *rex_game_obstacle_get_collision_collection(struct rex_game_object *obstacle)
{
    switch (obstacle->detail.obstacle)
    {
    case REX_GAME_OBSTACLE_PTERODACTYL:
        return &rex_collision_collections[REX_PTERODACTYL_COLLISION_COLLECTION_INDEX];
    case REX_GAME_OBSTACLE_CACTUS_SMALL_0:
        return &rex_collision_collections[REX_CACTUS_SMALL_0_COLLISION_COLLECTION_INDEX];
    case REX_GAME_OBSTACLE_CACTUS_SMALL_1:
        return &rex_collision_collections[REX_CACTUS_SMALL_1_COLLISION_COLLECTION_INDEX];
    case REX_GAME_OBSTACLE_CACTUS_SMALL_2:
        return &rex_collision_collections[REX_CACTUS_SMALL_2_COLLISION_COLLECTION_INDEX];
    case REX_GAME_OBSTACLE_CACTUS_LARGE_0:
        return &rex_collision_collections[REX_CACTUS_LARGE_0_COLLISION_COLLECTION_INDEX];
    case REX_GAME_OBSTACLE_CACTUS_LARGE_1:
        return &rex_collision_collections[REX_CACTUS_LARGE_1_COLLISION_COLLECTION_INDEX];
    case REX_GAME_OBSTACLE_CACTUS_LARGE_2:
        return &rex_collision_collections[REX_CACTUS_LARGE_2_COLLISION_COLLECTION_INDEX];
    }
}

struct rex_collision_collection *rex_game_object_get_collision_collection(struct rex_game_object *object)
{
    switch (object->type)
    { /* ignore decoration object */
    case REX_GAME_OBJECT_TREX:
        return rex_game_trex_get_collision_collection(object);
    case REX_GAME_OBJECT_OBSTACLE:
        return rex_game_obstacle_get_collision_collection(object);
    }
}

struct rex_collision_collection rex_game_object_get_real_collision_collection(struct rex_game_object *object)
{
    struct rex_collision_collection collection;
    struct rex_collision_collection *raw = rex_game_object_get_collision_collection(object);

    collection.amount = raw->amount;

    for (unsigned char i = 0; i < raw->amount; i++)
    {
        collection.boxes[i].x = raw->boxes[i].x + object->x;
        collection.boxes[i].y = raw->boxes[i].y + object->y;
        collection.boxes[i].width = raw->boxes[i].width;
        collection.boxes[i].height = raw->boxes[i].height;
    }

    return collection;
}

/* shouldn't call this function in other place */
nk_bool _rex_game_collision_detect(struct rex_game_object *object1, struct rex_game_object *object2)
{
    {
        /* coarse-grained detection */
        struct collision_box box1;
        struct collision_box box2;

        box1.x = object1->x;
        box1.y = object1->y;
        box1.width = object1->width;
        box1.height = object1->height;

        box2.x = object2->x;
        box2.y = object2->y;
        box2.width = object2->width;
        box2.height = object2->height;

        if (collision_detect(&box1, &box2) == nk_false)
            return nk_false;
    }
    {
        /* fine-grained detection */
        struct rex_collision_collection collection1 = rex_game_object_get_real_collision_collection(object1);
        struct rex_collision_collection collection2 = rex_game_object_get_real_collision_collection(object2);

        if (collection1.amount == 0 && collection2.amount == 0)
            return nk_false;

        for (unsigned char i = 0; i < collection1.amount; i++)
        { /* iterate collection1 boxes */
            for (unsigned char j = 0; j < collection2.amount; j++)
            { /* iterate collection2 boxes */
                if (collision_detect(&collection1.boxes[i], &collection2.boxes[j]) == nk_true)
                    return nk_true;
            }
        }

        return nk_false;
    }
}

nk_bool rex_game_collision_detect(void)
{
    struct rex_game_object *object1 = rex_game_get_closest_obstacle();
    struct rex_game_object *object2 = rex_object_get_trex();

    if (object1 != NULL && object2 != NULL)
        return _rex_game_collision_detect(object1, object2);

    return nk_false;
}

void rex_game_init_trex_walk_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* trex_walk collision collection */
        collection = &rex_collision_collections[REX_TREX_WALK_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for trex_walk*/
        collection->amount = 4;
        { /* trex_walk collision box 0 */
            collection->boxes[0].x = 4;
            collection->boxes[0].y = 42;
            collection->boxes[0].width = 56;
            collection->boxes[0].height = 28;
        }
        { /* trex_walk collision box 1 */
            collection->boxes[1].x = 20;
            collection->boxes[1].y = 70;
            collection->boxes[1].width = 32;
            collection->boxes[1].height = 20;
        }
        { /* trex_walk collision box 2 */
            collection->boxes[2].x = 44;
            collection->boxes[2].y = 4;
            collection->boxes[2].width = 40;
            collection->boxes[2].height = 30;
        }
        { /* trex_walk collision box 3 */
            collection->boxes[3].x = 60;
            collection->boxes[3].y = 42;
            collection->boxes[3].width = 8;
            collection->boxes[3].height = 8;
        }
    }
}

void rex_game_init_trex_duck_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* trex_duck collision collection */
        collection = &rex_collision_collections[REX_TREX_DUCK_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for trex_duck */
        collection->amount = 1;
        { /* trex_duck collision box 0 */
            collection->boxes[0].x = 78;
            collection->boxes[0].y = 6;
            collection->boxes[0].width = 36;
            collection->boxes[0].height = 30;
        }
    }
}

void rex_game_init_cactus_large_0_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* cactus_large_0 collision collection */
        collection = &rex_collision_collections[REX_CACTUS_LARGE_0_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for cactus_large_0 */
        collection->amount = 3;
        { /* cactus_large_0 collision box 0 */
            collection->boxes[0].x = 2;
            collection->boxes[0].y = 26;
            collection->boxes[0].width = 10;
            collection->boxes[0].height = 32;
        }
        { /* cactus_large_0 collision box 1 */
            collection->boxes[1].x = 18;
            collection->boxes[1].y = 2;
            collection->boxes[1].width = 14;
            collection->boxes[1].height = 24;
        }
        { /* cactus_large_0 collision box 2 */
            collection->boxes[2].x = 38;
            collection->boxes[2].y = 22;
            collection->boxes[2].width = 10;
            collection->boxes[2].height = 32;
        }
    }
}

void rex_game_init_cactus_large_1_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* cactus_large_1 collision collection */
        collection = &rex_collision_collections[REX_CACTUS_LARGE_1_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for cactus_large_1 */
        collection->amount = 3;
        { /* cactus_large_1 collision box 0 */
            collection->boxes[0].x = 2;
            collection->boxes[0].y = 26;
            collection->boxes[0].width = 10;
            collection->boxes[0].height = 32;
        }
        { /* cactus_large_1 collision box 1 */
            collection->boxes[1].x = 18;
            collection->boxes[1].y = 12;
            collection->boxes[1].width = 64;
            collection->boxes[1].height = 14;
        }
        { /* cactus_large_1 collision box 2 */
            collection->boxes[2].x = 88;
            collection->boxes[2].y = 22;
            collection->boxes[2].width = 10;
            collection->boxes[2].height = 32;
        }
    }
}

void rex_game_init_cactus_large_2_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* cactus_large_2 collision collection */
        collection = &rex_collision_collections[REX_CACTUS_LARGE_2_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for cactus_large_2 */
        collection->amount = 3;
        { /* cactus_large_2 collision box 0 */
            collection->boxes[0].x = 2;
            collection->boxes[0].y = 26;
            collection->boxes[0].width = 10;
            collection->boxes[0].height = 32;
        }
        { /* cactus_large_2 collision box 1 */
            collection->boxes[1].x = 18;
            collection->boxes[1].y = 16;
            collection->boxes[1].width = 114;
            collection->boxes[1].height = 10;
        }
        { /* cactus_large_2 collision box 2 */
            collection->boxes[2].x = 138;
            collection->boxes[2].y = 24;
            collection->boxes[2].width = 10;
            collection->boxes[2].height = 30;
        }
    }
}

void rex_game_init_cactus_small_0_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* cactus_small_0 collision collection */
        collection = &rex_collision_collections[REX_CACTUS_SMALL_0_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for cactus_small_0 */
        collection->amount = 3;
        { /* cactus_small_0 collision box 0 */
            collection->boxes[0].x = 2;
            collection->boxes[0].y = 18;
            collection->boxes[0].width = 6;
            collection->boxes[0].height = 24;
        }
        { /* cactus_small_0 collision box 1 */
            collection->boxes[1].x = 12;
            collection->boxes[1].y = 2;
            collection->boxes[1].width = 10;
            collection->boxes[1].height = 16;
        }
        { /* cactus_small_0 collision box 2 */
            collection->boxes[2].x = 26;
            collection->boxes[2].y = 10;
            collection->boxes[2].width = 6;
            collection->boxes[2].height = 24;
        }
    }
}

void rex_game_init_cactus_small_1_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* cactus_small_1 collision collection */
        collection = &rex_collision_collections[REX_CACTUS_SMALL_1_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for cactus_small_1 */
        collection->amount = 3;
        { /* cactus_small_1 collision box 0 */
            collection->boxes[0].x = 2;
            collection->boxes[0].y = 18;
            collection->boxes[0].width = 6;
            collection->boxes[0].height = 24;
        }
        { /* cactus_small_1 collision box 1 */
            collection->boxes[1].x = 12;
            collection->boxes[1].y = 10;
            collection->boxes[1].width = 44;
            collection->boxes[1].height = 8;
        }
        { /* cactus_small_1 collision box 2 */
            collection->boxes[2].x = 60;
            collection->boxes[2].y = 10;
            collection->boxes[2].width = 6;
            collection->boxes[2].height = 26;
        }
    }
}

void rex_game_init_cactus_small_2_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* cactus_small_2 collision collection */
        collection = &rex_collision_collections[REX_CACTUS_SMALL_2_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for cactus_small_2 */
        collection->amount = 3;
        { /* cactus_small_2 collision box 0 */
            collection->boxes[0].x = 2;
            collection->boxes[0].y = 18;
            collection->boxes[0].width = 6;
            collection->boxes[0].height = 24;
        }
        { /* cactus_small_2 collision box 1 */
            collection->boxes[1].x = 12;
            collection->boxes[1].y = 10;
            collection->boxes[1].width = 78;
            collection->boxes[1].height = 8;
        }
        { /* cactus_small_2 collision box 2 */
            collection->boxes[2].x = 94;
            collection->boxes[2].y = 10;
            collection->boxes[2].width = 6;
            collection->boxes[2].height = 26;
        }
    }
}

void rex_game_init_pterodactyl_collision_collection(void)
{
    struct rex_collision_collection *collection;
    { /* pterodactyl collision collection */
        collection = &rex_collision_collections[REX_PTERODACTYL_COLLISION_COLLECTION_INDEX];
        /* total collision boxes for pterodactyl */
        collection->amount = 3;
        { /* pterodactyl collision box 0 */
            collection->boxes[0].x = 4;
            collection->boxes[0].y = 24;
            collection->boxes[0].width = 28;
            collection->boxes[0].height = 12;
        }
        { /* pterodactyl collision box 1 */
            collection->boxes[1].x = 36;
            collection->boxes[1].y = 24;
            collection->boxes[1].width = 36;
            collection->boxes[1].height = 40;
        }
        { /* pterodactyl collision box 2 */
            collection->boxes[2].x = 64;
            collection->boxes[2].y = 40;
            collection->boxes[2].width = 16;
            collection->boxes[2].height = 16;
        }
    }
}

void rex_game_init_rex_collision_collections(void)
{
    rex_game_init_trex_walk_collision_collection();
    rex_game_init_trex_duck_collision_collection();
    rex_game_init_cactus_large_0_collision_collection();
    rex_game_init_cactus_large_1_collision_collection();
    rex_game_init_cactus_large_2_collision_collection();
    rex_game_init_cactus_small_0_collision_collection();
    rex_game_init_cactus_small_1_collision_collection();
    rex_game_init_cactus_small_2_collision_collection();
    rex_game_init_pterodactyl_collision_collection();
}
