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
#define REX_TREX_WALK_COLLISION_COLLECTION_INDEX 0
#define REX_TREX_DUCK_COLLISION_COLLECTION_INDEX 1
#define REX_CACTUS_LARGE_0_COLLISION_COLLECTION_INDEX 2
#define REX_CACTUS_LARGE_1_COLLISION_COLLECTION_INDEX 3
#define REX_CACTUS_LARGE_2_COLLISION_COLLECTION_INDEX 4
#define REX_CACTUS_SMALL_0_COLLISION_COLLECTION_INDEX 5
#define REX_CACTUS_SMALL_1_COLLISION_COLLECTION_INDEX 6
#define REX_CACTUS_SMALL_2_COLLISION_COLLECTION_INDEX 7
#define REX_PTERODACTYL_COLLISION_COLLECTION_INDEX 8

#define REX_COLLISION_COLLECTION_MAX_SIZE 9 /* 1 is for trex */

static struct rex_collision_collection rex_collision_collections[REX_COLLISION_COLLECTION_MAX_SIZE];
