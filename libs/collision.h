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
