#ifndef MAPSELECT_H
#define MAPSELECT_H

#include <raylib.h>
#include <ui/Button.h>

struct map_select
{
    char map_names[64][256];
    Texture map_icons[64];
    int map_count;
    int map_select;
    BUTTON add;
    BUTTON sub;
    BUTTON go;
};
typedef struct map_select MAPSELECT;

void* mapselect_init();
void mapselect_free(MAPSELECT* map);
void mapselect_update(MAPSELECT* map);
void mapselect_render(MAPSELECT* map);

#endif // MAPSELECT_H
