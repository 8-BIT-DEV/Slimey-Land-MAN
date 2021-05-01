/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>
#include <raylib.h>
#include <ui/Button.h>

#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

#include <plugin/Plugin.h>

#include <object/Defaults.h>

// scenes
#include <scenes/Game.h>
#include <scenes/MainMenu.h>

// gamejolt!
#ifdef WIN32
#include <gj.h>
// forced to turn off the api for windows :(
#else
#include <gj.h>
#endif // WIN32

char* DEVELOPER = "HAHA FUNNY";
char* whatsthis = "WIN32_DLL_LINK";

Color bg_color = BLACK;
//char* map_name = "test_map"; old code uneeded
char* map_name;

void (*scene_update)(void* data);
void (*scene_render)(void* data);
void (*data_f)(void* data);
void* scene_data;
bool scene_got = false;
int scene_id = 0;
bool oh_no = false;

int logged = 0;
bool exitnow = false;

char* version_string = "0.7.10";

bool sparkles_has = false;
Color sparkle_color = BLUE;

Texture default_background;

// sparkle textures
Texture sparkle1;

void* yes(int what)
{
    printf("WHAT A CRASH!\n");
    return NULL;
}

void InitGame()
{
    #ifndef WIN32
    set_id("put a gj game id here");
    set_pkey("put a gj private key here");
    #endif // WIN32
    InitWindow(1280, 720, "SLIMEY LAND MAN");
    SetWindowState(FLAG_VSYNC_HINT);
    SetExitKey(KEY_KP_SUBTRACT);
    InitAudioDevice();
    SetTargetFPS(60);
    default_background = LoadTexture("res/textures/misc/background.png");
    sparkle1 = LoadTexture("res/textures/misc/sparkle1.png");
    map_name = malloc(256);
    //strcpy(map_name, "test_map");
    //ChangeScene(game_update, game_render, game_init, game_free);
    ChangeScene(mainmenu_update, mainmenu_render, mainmenu_init, mainmenu_free);
    InitCorePlugins();
    // gamejolt stuff
    #ifndef WIN32
    if(!access(".gj-credentials", F_OK))
    {
        logged = true;
        printf("LOGIN INFO FOUND FROM .gj-credentials\n");
        FILE* details = fopen(".gj-credentials", "rb");
        fseek(details, 0, SEEK_END);
        int len = ftell(details);
        fseek(details, 0, SEEK_SET);
        char* data = malloc(len);
        fread(data, len, 1, details);
        char* tokens[4];
        int status = tokenize(tokens, data, 4, "\n");
        printf("USERNAME:%s TOKEN:%s\n", tokens[1], tokens[2]);
        int gj_stat = gj_login(tokens[1], tokens[2]);
        if(gj_stat == 0) logged = -1;
        else
        {
            logged = 1;
            http_get_response_t* got = http_get(FormatText("8bitdevgames.com/slm/api/has.php?name=%s&type=1", tokens[0]));
            if(strcmp(got->data, "f") != 0)
            {
                printf("YES!!!!!!\n");
                sparkles_has = true;
                char* coltok[4];
                int colcount = tokenize(coltok, got->data, 4, " ");
                sparkle_color = (Color){atoi(coltok[0]), atoi(coltok[1]), atoi(coltok[2]), 255};
                tokenize_free(coltok, colcount);
            } else
            {
                printf("NOOOO\n");
            }
            http_get_free(got);
        }
        tokenize_free(tokens, status);
        free(data);
        fclose(details);
    } else if(!access(".login-info", F_OK))
    {
        logged = true;
        printf("LOGIN INFO FOUND FROM .login-info\n");
        FILE* details = fopen(".login-info", "rb");
        fseek(details, 0, SEEK_END);
        int len = ftell(details);
        fseek(details, 0, SEEK_SET);
        char* data = malloc(len);
        fread(data, len, 1, details);
        char* tokens[4];
        int status = tokenize(tokens, data, 4, "\n");
        printf("USERNAME:%s TOKEN:%s\n", tokens[0], tokens[1]);
        int gj_stat = gj_login(tokens[0], tokens[1]);
        gj_give_trophie(140728);
        if(gj_stat == 0) logged = -1;
        else
        {
            logged = 1;
            http_get_response_t* got = http_get(FormatText("8bitdevgames.com/slm/api/has.php?name=%s&type=1", tokens[0]));
            if(strcmp(got->data, "f") != 0)
            {
                printf("YES!!!!!!\n");
                sparkles_has = true;
                char* coltok[4];
                int colcount = tokenize(coltok, got->data, 4, " ");
                sparkle_color = (Color){atoi(coltok[0]), atoi(coltok[1]), atoi(coltok[2]), 255};
                tokenize_free(coltok, colcount);
            } else
            {
                printf("NOOOO\n");
            }
            http_get_free(got);
        }
        tokenize_free(tokens, status);
        free(data);
        fclose(details);
    } else
    {
        printf("NO LOGIN INFO FOUND\n");
    }
    #endif // WIN32
}

void FreeGame()
{
    if(scene_got == true)
    {
        data_f(scene_data);
        free(scene_data);
    }
    free(map_name);
    UnloadTexture(default_background);
    UnloadTexture(sparkle1);
    CleanPlugins();
    CloseAudioDevice();
    CloseWindow();
    #ifndef WIN32
    FILE* dump = fopen("res/memdump.log", "w");
    malloc_info(0, dump);
    fclose(dump);
    #endif // WIN32
}

void UpdateGame()
{
    if(scene_got == true)
    {
        scene_update(scene_data);
    }
}

void RenderGame()
{
    BeginDrawing();
    ClearBackground(bg_color);
    if(scene_got == true)
    {
        scene_render(scene_data);
    }
    DrawFPS(0, 0);
    EndDrawing();
}

int main()
{
    printf("USING %d\n", __STDC_VERSION__);
    InitGame();

    while(WindowShouldClose() == false && exitnow == false)
    {
        if(IsKeyPressed(KEY_F2))
        {
            time_t t = time(NULL);
            struct tm* tptr = localtime(&t);
            char* tim = malloc(64);
            strftime(tim, 64, "%c", tptr);
            printf("TIME:%s\n", tim);
            TakeScreenshot(FormatText("screenshots/screenshot %s.png", tim));
            free(tim);
        }
        RenderGame();
        UpdateGame();
    }

    FreeGame();
    return 0;
}
