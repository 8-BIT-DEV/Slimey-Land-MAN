#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arraylist.h>

#include <raylib.h>

// needed some ui declarations too
struct button
{
    int got_button;
    char* text;
    Texture tex;
    bool use_tex;
    Vector2 d;
    void (*callback)(void* args);
    void* callback_arg;
};
typedef struct button BUTTON;

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

struct plugin
{
    char* name;
    char* desc;
    bool spawnable;
    float expir;
    Texture tex;
    void* (*init)();
    void (*on_collision)(void* self, void* other);
    void (*update_callback)(void* self, void* game);
    void (*render_callback)(void* self);
};
typedef struct plugin PLUGIN;

struct hitbox
{
    Rectangle core;
    Rectangle top;
    Rectangle bottom;
    Rectangle left;
    Rectangle right;
};
typedef struct hitbox BOX;

struct game_object
{
    int x;
    int y;
    Vector2 oldpos;
    float rot;
    float expir;
    int id;
    void* data;
    BOX area;
    Texture tex;
    PLUGIN* funcs;
};
typedef struct game_object GAMEOBJECT;

void (*spawn_object)(void* game, char* name, int x, int y, float rot);
void (*despawn_object)(void* game, int id);

void (*AddPluginM)(char* name, char* desc, bool spawnable, float expir, Texture tex, Texture icon, void (*on_collision)(void* self, void* other), void (*update_callback)(void* self, void* game), void (*render_callback)(void* self), void* (data_init)());
void (*RemovePlugin)(char* name);
PLUGIN* (*GetPlugin)(char* name);
void (*spawn_effect)(GAME* game, int count, int rad, float speed, float expir_min, float expirt_max, Color start, int x, int y);

// !! DO NOT MODIFY ANY CODE BELOW AS IT WILL CAUSE ERRORS WITH THE PLUGIN LOADER OR ISSUES CREATING A PLUGIN !!

char* get_version()
{
	return "0.7.10";
}

void loadcallbacks(void (*so)(), void (*dso)(), void (*apm)(), void (*rp)(), void (*gp)(), void (*se)())
{
	spawn_object = so;
	despawn_object = dso;
	AddPluginM = apm;
	RemovePlugin = rp;
	GetPlugin = gp;
	spawn_effect = se;
}
