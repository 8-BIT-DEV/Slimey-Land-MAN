#include <object/Defaults.h>
#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <scenes/Game.h>

// this isnt my code ripped it right from stackoverflow
float RandomFloat(float min, float max){
   return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void update_object(GAMEOBJECT* self, GAME* game)
{
    if(self->expir != -1)
    {
        self->expir -= GetFrameTime();
        //printf("TIME LEFT:%f\n", self->expir);
        if(self->expir <= 0)
        {
            despawn_object(game, self->id);
            return;
        }
    }
    if(self->funcs->update_callback != NULL)
    {
        self->funcs->update_callback(self, game);
    }
    for(int x = self->x / 32 - 4; x < self->x / 32 + 4; x++)
    {
        for(int y = self->y / 32 - 4; y < self->y / 32 + 4; y++)
        {
            if(x > -1 && y > -1)
            {
                if(game->map.tiles[y*game->map.width+x] < 23)
                {
                    Rectangle that = (Rectangle){x * 32, y * 32, 32, 32};
                    if(CheckCollisionRecs(self->area.top, that))
                    {
                        if((self->y - self->oldpos.y) < 0)
                        {
                            self->y = that.y + 31;
                        }
                    }
                    if(CheckCollisionRecs(self->area.bottom, that))
                    {
                        if((self->y - self->oldpos.y) > 0)
                        {
                            self->y = that.y - 31;
                        }
                    }
                    if(CheckCollisionRecs(self->area.left, that))
                    {
                        if((self->x - self->oldpos.x) < 0)
                        {
                            self->x = that.x + 31;
                        }
                    }
                    if(CheckCollisionRecs(self->area.right, that))
                    {
                        if((self->x - self->oldpos.x) > 0)
                        {
                            self->x = that.x - 31;
                        }
                    }
                }
            }
        }
    }
    self->area.core = (Rectangle){self->x, self->y, self->tex.width, self->tex.height};
    self->area.top = (Rectangle){self->x + 4, self->y, self->tex.width - 8, 4};
    self->area.bottom = (Rectangle){self->x + 4, self->y + (self->tex.height - 4), self->tex.width - 8, 4};
    self->area.left = (Rectangle){self->x, self->y + 4, 4, self->tex.height - 8};
    self->area.right = (Rectangle){self->x + (self->tex.width - 4), self->y + 4, 4, self->tex.height - 8};
    self->oldpos = (Vector2){self->x, self->y};
}

void render_object(GAMEOBJECT* self)
{
    //DrawTexture(self->tex, self->x, self->y, WHITE);
    DrawTextureEx(self->tex, (Vector2){self->x, self->y}, self->rot, 1, WHITE);
    if(self->funcs->render_callback != NULL)
    {
        self->funcs->render_callback(self);
    }
}


// !! DO NOT TRY TO USE THESE FUNCTIONS THEY ARE WASTE AND OLD !!
GAMEOBJECT* gen_object(char* name)
{
    GAMEOBJECT* object = malloc(sizeof(GAMEOBJECT));
    object->funcs = GetPlugin(name);
    object->id = -1;
    object->expir = object->funcs->expir;
    object->rot = 0;
    object->x = 0;
    object->y = 0;
    object->tex = object->funcs->tex;;
    object->data = object->funcs->init();
    return object;
}

void spawn_effect(GAME* game, int count, int rad, float speed, float expir_min, float expir_max, Color start, int x, int y)
{
    GAMEOBJECT* system = gen_object("effect_system");
    system->id = game->objects->size;
    PARTICLESYSTEM* data = system->data;
    data->base_count = count;
    data->current_count = count;
    data->start = start;
    for(int i = 0; i < count; i++)
    {
        data->effect[i].expir = GetRandomValue((int)expir_min, (int)expir_max);
        data->effect[i].rad = rad;
        data->effect[i].dir = (Vector2){GetRandomValue(-10, 10), GetRandomValue(-10, 10)};
        data->effect[i].speed = speed;
        data->effect[i].x = x;
        data->effect[i].y = y;
        data->effect[i].use = true;
        data->effect[i].age = 0;
    }
    arraylist_add(game->objects, system);
}

void spawn_object(GAME* game, char* name, int x, int y, float rot)
{
    GAMEOBJECT* object = malloc(sizeof(GAMEOBJECT));
    object->funcs = GetPlugin(name);
    object->id = game->objects->size;
    object->expir = object->funcs->expir;
    object->rot = rot;
    object->x = x;
    object->y = y;
    object->tex = object->funcs->tex;;
    object->data = object->funcs->init();
    arraylist_add(game->objects, object);
}

void despawn_object(GAME* game, int id)
{
    GAMEOBJECT* object = arraylist_get(game->objects, id);
    free(object->data);
    arraylist_remove(game->objects, id);
    for(int i = id; i < game->objects->size; i++)
    {
        GAMEOBJECT* o = arraylist_get(game->objects, i);
        printf("NEW ID:%d OLD ID:%d SIZE:%d NAME:%s\n", i, o->id, game->objects->size, o->funcs->name);
        o->id = i;
    }
    printf("\n\n\n\n\n");
}
