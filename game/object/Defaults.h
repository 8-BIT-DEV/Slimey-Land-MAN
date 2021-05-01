#ifndef GOBJECT_DEFAULTS_H
#define GOBJECT_DEFAULTS_H

#include <raylib.h>
#include <object/GameObject.h>
#include <scenes/Game.h>

#include <stdbool.h>;

struct particle
{
    int x;
    int y;
    int rad;
    Vector2 dir;
    float speed;
    float expir;
    float age;
    bool use;
};
typedef struct particle PARTICLE;

struct particle_system
{
    PARTICLE effect[1204];
    int current_count;
    int base_count;
    Color start;
};
typedef struct particle_system PARTICLESYSTEM;

// we can never be sure why i put particles in defaults
void* effect_init();
void effect_update(GAMEOBJECT* self, GAME* game);
void effect_render(GAMEOBJECT* self);

void update_object(GAMEOBJECT* self, GAME* game);
void render_object(GAMEOBJECT* self);

void spawn_object(GAME* game, char* name, int x, int y, float rot);
void despawn_object(GAME* game, int id);

GAMEOBJECT* gen_object(char* name);

void spawn_effect(GAME* game, int count, int rad, float speed, float expir_min, float expirt_max, Color start, int x, int y);

#endif // GOBJECT_DEFAULTS_H
