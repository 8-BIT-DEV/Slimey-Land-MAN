#include <raylib.h>
#include <object/GameObject.h>
#include <object/Defaults.h>

#include <scenes/Game.h>

struct tt
{
    int c;
};

void* test_init()
{
    struct tt* t = malloc(sizeof(struct tt));
    t->c = 0;
    return t;
}

void test_update(GAMEOBJECT* self, GAME* game)
{
    struct tt* t = self->data;
    if(t->c == 0) spawn_effect(game, 100, 8, 1.1, 1, 3, RED, self->x, self->y);
    t->c = 1;
    self->rot += 0.1;
}
