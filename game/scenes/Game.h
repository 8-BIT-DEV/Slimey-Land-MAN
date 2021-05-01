#ifndef GAME_H
#define GAME_H

#include <arraylist.h>
#include <raylib.h>
#include <ui/Button.h>

struct menu
{
};
typedef struct menu MENU;

struct tile_map
{
    unsigned int* tiles;
    unsigned int width;
    unsigned int height;
};
typedef struct tile_map TILEMAP;

struct game
{
    TILEMAP map;
    Texture tiletex[256];
    int texcount;
    arraylist* objects;
    int ply_id;
    Camera2D cam;
    bool paused;
    BUTTON resume;
    BUTTON back;
    int in_off;
};
typedef struct game GAME;

void* game_init();
void game_free(GAME* game);
void game_update(GAME* game);
void game_render(GAME* game);

#endif // GAME_H
