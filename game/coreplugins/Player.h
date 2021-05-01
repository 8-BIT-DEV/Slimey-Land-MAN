#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include <object/Defaults.h>
#include <object/GameObject.h>
#include <scenes/Game.h>

#include <raylib.h>

struct sparkle
{
    float x;
    float y;
    float age;
    float fall_age;
    bool use;
};
typedef struct sparkle SPARKLE;

struct ply
{
    int what;
    int got;
    int use;
    bool has_sparkles;
    Color sparkle_color;
    float next;
    float next_timer;
    SPARKLE effect[16];
    Vector2 target;
    GAME* game;
};
typedef struct ply PLAYER;

void* player_init();
void player_update(GAMEOBJECT* self, GAME* game);
void player_render(GAMEOBJECT* self);

#endif // PLAYER_H
