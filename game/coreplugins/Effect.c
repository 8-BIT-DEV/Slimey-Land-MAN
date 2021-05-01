#include <scenes/Game.h>
#include <object/Defaults.h>
#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void* effect_init()
{
    PARTICLESYSTEM* data = malloc(sizeof(PARTICLESYSTEM));
    data->base_count = 100;
    data->current_count = 100;
    data->start = RED;
    for(int i = 0; i < 100; i++)
    {
        data->effect[i].expir = GetRandomValue((int)1, (int)3);
        data->effect[i].rad = 4;
        data->effect[i].dir = (Vector2){GetRandomValue(-10, 10), GetRandomValue(-10, 10)};
        data->effect[i].speed = 1.1;
        data->effect[i].x = 0;
        data->effect[i].y = 0;
        data->effect[i].use = true;
        data->effect[i].age = 0;
    }
    return data;
}

void effect_update(GAMEOBJECT* self, GAME* game)
{
    PARTICLESYSTEM* system = self->data;
    for(int i = 0; i < system->base_count; i++)
    {
        if(system->effect[i].use == true)
        {
            system->effect[i].x += (int)system->effect[i].dir.x * system->effect[i].speed;
            system->effect[i].y += (int)system->effect[i].dir.y * system->effect[i].speed;
            system->effect[i].age += GetFrameTime();
            if(system->effect[i].age > system->effect[i].expir)
            {
                system->effect[i].use = false;
                system->current_count--;
            }
            //printf("I:%d THRE:%d %d %d %f %f\n", i, system->current_count, system->effect[i].x, system->effect[i].y, system->effect[i].dir.x, system->effect[i].dir.y);
        }
    }
    if(system->current_count <= 0)
    {
        despawn_object(game, self->id);
        printf("CLEANING UP EFFECT SYSTEM\n");
        return;
    }
}

void effect_render(GAMEOBJECT* self)
{
    PARTICLESYSTEM* system = self->data;
    for(int i = 0; i < system->current_count; i++)
    {
        if(system->effect[i].use == true) DrawCircle(system->effect[i].x, system->effect[i].y, system->effect[i].rad, system->start);
    }
}
