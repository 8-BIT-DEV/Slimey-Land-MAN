#ifndef GOBJECT_H
#define GOBJECT_H

#include <plugin/Plugin.h>
#include <raylib.h>

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

#endif // GOBJECT_H
