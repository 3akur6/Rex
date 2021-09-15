enum rex_game_object_type
{
    REX_GAME_OBJECT_TREX = 1,   /* trex */
    REX_GAME_OBJECT_OBSTACLE,   /* obstacle */
    REX_GAME_OBJECT_DECORATION, /* decoration */
};

enum rex_game_trex_type
{
    REX_GAME_TREX_STATIC,
    REX_GAME_TREX_WALK,
    REX_GAME_TREX_JUMP,
    REX_GAME_TREX_DUCK,
};

enum rex_game_obstacle_type
{
    REX_GAME_OBSTACLE_PTERODACTYL,
    REX_GAME_OBSTACLE_CACTUS_SMALL_0,
    REX_GAME_OBSTACLE_CACTUS_SMALL_1,
    REX_GAME_OBSTACLE_CACTUS_SMALL_2,
    REX_GAME_OBSTACLE_CACTUS_LARGE_0,
    REX_GAME_OBSTACLE_CACTUS_LARGE_1,
    REX_GAME_OBSTACLE_CACTUS_LARGE_2,
};

enum rex_game_decoration_type
{
    REX_GAME_DECORATION_CLOUD,
};

struct rex_game_object
{
    nk_bool active;
    enum rex_game_object_type type;
    union
    {
        enum rex_game_object_type obstacle;
        enum rex_game_decoration_type decoration;
        enum rex_game_trex_type trex;
    } detail;
    float x;
    float y;
    unsigned int width;
    unsigned int height;
    unsigned int create_at_frame;
    unsigned int destroy_at_frame;
};