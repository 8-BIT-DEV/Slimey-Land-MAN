#include <scenes/Game.h>
#include <scenes/MainMenu.h>
#include <object/Defaults.h>
#include <object/GameObject.h>

#include <tmx.h>
#include <raylib.h>
#include <tokenizer.h>

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

extern char* map_name;
extern Color bg_color;

void resume_map(GAME* game)
{
    game->paused = false;
}

void leave_map(GAME* game)
{
    ChangeScene(mainmenu_update, mainmenu_render, mainmenu_init, mainmenu_free);
}

void load_materials(GAME* game, char* mat)
{
    char* materialpath = malloc(4096);
    strcpy(materialpath, "res/materials/");
    strcat(materialpath, mat);
    strcat(materialpath, ".int");
    FILE* materialfile = fopen(materialpath, "rb");
    if(materialfile == NULL)
    {
        printf("ERR NO MATERIALS WITH THAT NAME\n", materialpath);
        free(materialpath);
        exit(-1);
    }
    int matlen = 0;
    fseek(materialfile, 0, SEEK_END);
    matlen = ftell(materialfile);
    fseek(materialfile, 0, SEEK_SET);
    char* data = malloc(matlen);
    fread(data, matlen, 1, materialfile);

    char* tokens[256];
    int token_ret = tokenize(tokens, data, 256, " ");
    if(token_ret == MAX_TOKENS_REACHED)
    {
        printf("ERR WITH MATERIAL PARSING : MAX_TOKENS\n", token_ret);
        exit(-1);
    } else if(token_ret == NULL_BUFFER)
    {
        printf("ERR WITH MATERIAL PARSING : NULL_BUFFER\n", token_ret);
        exit(-1);
    } else if(token_ret == MEMORY_ERROR)
    {
        printf("ERR WITH MATERIAL PARSING : MEMORY_ERROR\n", token_ret);
        exit(-1);
    }
    for(int i = 1; i < token_ret - 1; i++)
    {
        printf("I:%d\n", i);
        game->tiletex[game->texcount] = LoadTexture(tokens[i]);
        game->texcount++;
    }

    tokenize_free(tokens, token_ret);
    free(data);
    free(materialpath);
    fclose(materialfile);
}

void load_map(GAME* game, tmx_map* map)
{
    game->cam.offset = (Vector2){1280/2,720/2};
    game->cam.zoom = 1.5;

    game->map.width = map->width;
    game->map.height = map->height;
    game->map.tiles = malloc((game->map.width*game->map.height)*sizeof(int));
    memset(game->map.tiles, 220, map->width*map->height*sizeof(int));

    for(int x = 0; x < game->map.width; x++)
    {
        for(int y = 0; y < game->map.height; y++)
        {
            int get = map->ly_head->content.gids[y*game->map.width+x] & TMX_FLIP_BITS_REMOVAL;
            if(map->tiles[get] != NULL)
            {
                if(map->tiles[get]->id == 0)
                {
                    game->cam.target = (Vector2){x * 32 + 16, y * 32 + 16};
                    game->cam.rotation = 0;
                    game->ply_id = game->objects->size;
                    spawn_object(game, "Player", x * 32, y * 32, 0);
                    printf("SPAWNING PLAYER IN MAP AT $# ^&&*\n");
                } else
                {
                    game->map.tiles[y*game->map.width+x] = map->tiles[get]->id;
                }
            }
        }
    }
}

void* game_init()
{
    printf("INIT GAME SCENE WITH MAP %s\n", map_name);
    SetSceneID(5);
    GAME* game = malloc(sizeof(GAME));
    game->texcount = 0;
    game->objects = arraylist_create();
    game->ply_id = -1;
    game->paused = false;
    game->in_off = 30;
    game->resume = create_button("RESUME", false, LoadTexture("dadadawdada"), (Vector2){256, 96}, resume_map, game);
    game->back = create_button("MAIN MENU", false, LoadTexture("dadadawdada"), (Vector2){256, 96}, leave_map, game);
    //game->in_off = 0;
    char* path = malloc(4096);
    char* root = malloc(4096);
    getcwd(root, 4096);
    //strcpy(path, root);
    strcpy(path, "res/maps/");
    strcat(path, map_name);
    strcat(path, ".tmx");
    tmx_map* map = tmx_load(/*"/home/redguy/Slimey Land MAN/res/maps/test_map.tmx"*/ path);
    if(map == NULL)
    {
        printf("ERR NO MAP WITH THAT NAME %s\n", path);
        tmx_perror("Cant load map");
        exit(-1);
    }
    free(root);
    free(path);
    tmx_property* mat = tmx_get_property(map->ly_head->properties, "mat");
    tmx_property* bg = tmx_get_property(map->ly_head->properties, "bg");
    if(mat == NULL || bg == NULL)
    {
        printf("INVALID MAP PROPERTIES\n");
        exit(-1);
    }
    tmx_col_floats col = tmx_col_to_floats(bg->value.color);
    bg_color = (Color){col.r * 255, col.g * 255, col.b * 255};

    load_materials(game, mat->value.string);
    load_map(game, map);

    tmx_free_func(map);

    if(game->ply_id == -1) printf("WARNING NO PLAYER WAS SPAWNED\n");

    return game;
}

void game_free(GAME* game)
{
    printf("CLEANING GAME\n");
    free(game->map.tiles);
    arraylist_destroy(game->objects);
    for(int i = 0; i < game->texcount; i++)
    {
        UnloadTexture(game->tiletex[i]);
    }
}

void game_update(GAME* game)
{
    if(IsKeyPressed(KEY_ESCAPE))
    {
        game->paused = !game->paused;
        ShowCursor();
        game->in_off = 30;
    }
    if(game->paused)
    {
        tick_button(&game->resume, (1280 - 256) / 2, 256);
        tick_button(&game->back, (1280 - 256) / 2, 256 + 96 + 44);
        return;
    }

    if(game->in_off != 0 && !IsMouseButtonDown(0)) game->in_off = 0;

    for(int i = 0; i < game->objects->size; i++)
    {
        update_object(arraylist_get(game->objects, i), game);
    }
    GAMEOBJECT* ply = arraylist_get(game->objects, game->ply_id);
    game->cam.target = (Vector2){ply->x, ply->y};
}

void game_render(GAME* game)
{
    BeginMode2D(game->cam);
    for(int x = 0; x < game->map.width; x++)
    {
        for(int y = 0; y < game->map.height; y++)
        {
            if(game->map.tiles[y*game->map.width+x] < 23)
            {
                DrawTexture(game->tiletex[game->map.tiles[y*game->map.width+x]], x * 32, y * 32, WHITE);
                //DrawText(FormatText("%d,%d", x, y), x * 32, y * 32, 16, WHITE);
            }
        }
    }
    for(int i = 0; i < game->objects->size; i++)
    {
        render_object(arraylist_get(game->objects, i));
    }
    ply_target_draw(arraylist_get(game->objects, game->ply_id));
    EndMode2D();
    //DrawRectangle(50, 50, 512, 512, GREEN);
    if(game->paused)
    {
        DrawText("PAUSED", (1280 - MeasureText("PAUSED", 62)) / 2 , 32, 62, WHITE);
        draw_button(&game->resume, (1280 - 256) / 2, 256, WHITE, RED, BLACK);
        draw_button(&game->back, (1280 - 256) / 2, 256 + 96 + 44, WHITE, RED, BLACK);
    } else
    {
        //printf("PLY:%d\n", game->ply_id);
        ply_ui(arraylist_get(game->objects, game->ply_id), game);
    }
}
