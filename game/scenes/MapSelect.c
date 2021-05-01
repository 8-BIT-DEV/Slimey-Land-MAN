#include <scenes/MapSelect.h>
#include <scenes/Game.h>
#include <dirent.h>
#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gj.h>

extern int logged;
extern Texture default_background;
extern char* map_name;

void go_up(MAPSELECT* map)
{
    if(map->map_select < map->map_count - 1)
    {
        map->map_select++;
    }
}

void go_down(MAPSELECT* map)
{
    if(map->map_select > 0)
    {
        map->map_select--;
    }
}

void go_map(MAPSELECT* map)
{
    strcpy(map_name, map->map_names[map->map_select]);
    printf("SELECTED MAP:%s\n", map_name);
    ChangeScene(game_update, game_render, game_init, game_free);
}

void* mapselect_init()
{
    MAPSELECT* map = malloc(sizeof(MAPSELECT));
    map->map_count = 0;
    map->map_select = 0;
    map->add = create_button("YOU FOUND A BUG!!!!", true, LoadTexture("res/textures/misc/arrowright.png"), (Vector2){128, 128}, go_up, map);
    map->sub = create_button("YOU FOUND A BUG!!!!", true, LoadTexture("res/textures/misc/arrowleft.png"), (Vector2){128, 128}, go_down, map);
    map->go = create_button("PLAY!", false, LoadTexture("res/textures/misc/arrowleft.png"), (Vector2){128, 128}, go_map, map);
    DIR* mapdir = opendir("res/maps");
    struct dirent* files;
    while((files = readdir(mapdir)) != NULL)
    {
        if(strcmp(files->d_name + strlen(files->d_name) - 4, ".tmx") == 0)
        {
            //printf("MAP FILE FOUND\n");
            printf("GOT MAP:%s\n", files->d_name);
            char pngname[512];
            strcpy(pngname, "res/maps/");
            strcat(pngname, files->d_name);
            strcat(pngname, ".png");
            printf("LOOKING FOR PREVIEW FILE:%s\n", pngname);
            if(access(pngname, F_OK) == 0)
            {
                printf("FOUND PREVIEW FILE\n");
                map->map_icons[map->map_count] = LoadTexture(pngname);
                strncpy(map->map_names[map->map_count], files->d_name, strlen(files->d_name) + 1);
                map->map_names[map->map_count][strlen(files->d_name) - 4] = '\0';
                printf("MAP INFO %s %d\n", map->map_names[map->map_count], map->map_icons[map->map_count].id);
            } else
            {
                printf("UNABLE TO FIND PREVIEW FILE FALLING BACK TO DEFAULT\n");
                map->map_icons[map->map_count] = LoadTexture("res/textures/misc/mapnoicon.png");
                strncpy(map->map_names[map->map_count], files->d_name, strlen(files->d_name) + 1);
                map->map_names[map->map_count][strlen(files->d_name) - 4] = '\0';
                printf("MAP INFO %s %d\n", map->map_names[map->map_count], map->map_icons[map->map_count].id);
            }
            map->map_count++;
        }
    }
    closedir(mapdir);
    if(map->map_count >= 10)
    {
        #ifndef WIN32
        gj_give_trophie(140726);
        #endif // WIN32
    }
    return map;
}

void mapselect_free(MAPSELECT* map)
{
    for(int i = 0; i < map->map_count; i++)
    {
        UnloadTexture(map->map_icons[i]);
    }
}

void mapselect_update(MAPSELECT* map)
{
    tick_button(&map->sub, 320, 40 + 360 + 100);
    tick_button(&map->add, 320 + 640 - 128, 40 + 360 + 100);
    tick_button(&map->go, 320 + (640 - 128) / 2, 40 + 360 + 100);
}

void mapselect_render(MAPSELECT* map)
{
    //printf("THIS IS LINE %d in FUNCTION %s in FILE %s\n", __LINE__, __func__, __FILE__);
    DrawTexture(default_background, 0, 0, WHITE);
    //draw_button(&map->add, 400, 40, WHITE, GREEN, RED);
    DrawRectangle(320, 40, 640, 360, RED);
    //DrawTexture(map->map_icons[map->map_select], 320, 40, WHITE);
    DrawTextureEx(map->map_icons[map->map_select], (Vector2){320, 40}, 0, 0.5, WHITE);
    DrawText(map->map_names[map->map_select], 320 + (640 - MeasureText(map->map_names[map->map_select], 59)) / 2, 40 + 360 + 10, 59, WHITE);
    draw_button(&map->sub, 320, 40 + 360 + 100, WHITE, WHITE, WHITE);
    draw_button(&map->add, 320 + 640 - 128, 40 + 360 + 100, WHITE, WHITE, WHITE);
    draw_button(&map->go, 320 + (640 - 128) / 2, 40 + 360 + 100, WHITE, RED, BLACK);
    #ifdef WIN32
    DrawText("GJ API TURNED OFF", (1280 - MeasureText("GJ API TURNED OFF", 36)), 685, 36, RED);
    #else
    if(logged == 0)
    {
        DrawText("NO GJ LOGIN INFO FOUND", (1280 - MeasureText("NO GJ LOGIN INFO FOUND", 36)), 685, 36, RED);
    } else if(logged == -1)
    {
        DrawText("INVALID GJ LOGIN INFO", (1280 - MeasureText("INVALID GJ LOGIN INFO", 36)), 685, 36, RED);
    } else if(logged == 1)
    {
        DrawText("LOGGED INTO GJ", (1280 - MeasureText("LOGGED INTO GJ", 36)), 685, 36, WHITE);
    }
    #endif // WIN32
}
