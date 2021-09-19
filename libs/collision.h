#define MAX_BOX_AMOUNT 10

struct collision_box
{
    float x;
    float y;
    unsigned int width;
    unsigned int height;
};

struct rex_collision_collection
{
    unsigned char amount; /* boxes amount */
    struct collision_box boxes[MAX_BOX_AMOUNT];
};

/* index for object collision collection in rex_collision_collections */
#define REX_TREX_COLLISION_COLLECTION_INDEX 0
#define REX_CACTUS_COLLISON_COLLECTION_INDEX 1

#define REX_COLLISION_COLLECTION_MAX_SIZE (REX_GAME_OBSTACLE_TYPE_AMOUNT + 1) /* 1 is for trex */

static struct rex_collision_collection rex_collision_collections[REX_COLLISION_COLLECTION_MAX_SIZE];
