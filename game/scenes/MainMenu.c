#include <scenes/MainMenu.h>
#include <scenes/Game.h>
#include <scenes/MapSelect.h>
#include <ui/Button.h>
#include <raylib.h>
#include <stdbool.h>


#include <stdio.h>

extern int logged;
extern bool exitnow;
extern Texture default_background;
extern char* version_string;

void play_game(void* arg)
{
    ChangeScene(mapselect_update, mapselect_render, mapselect_init, mapselect_free);
}

void exit_game(void* arg)
{
    exitnow = true;
}

void* mainmenu_init()
{
    MAINMENU* mainmenu = malloc(sizeof(MAINMENU));
    mainmenu->splash = "MY SPLASH";
    mainmenu->splash_timer = 0;
    mainmenu->b = create_button("MY BUTTON", false, LoadTexture("adsada"), (Vector2){256, 96}, NULL, NULL);
    mainmenu->play = create_button("PLAY", false, LoadTexture("dasdadwada"), (Vector2){256, 96}, play_game, NULL);
    mainmenu->exit = create_button("EXIT", false, LoadTexture("dasdadwada"), (Vector2){256, 96}, exit_game, NULL);
    //strcpy(mainmenu->v_string, "0.7.2");
    strcpy(mainmenu->v_string, version_string);
    #ifdef WIN32
    strcat(mainmenu->v_string, " WINDOWS");
    #else
    strcat(mainmenu->v_string, " LINUX");
    #endif // WIN32
    return mainmenu;
}

void mainmenu_free(MAINMENU* mainmenu)
{
}

void mainmenu_update(MAINMENU* mainmenu)
{
    if(IsGamepadAvailable(0))
    {
        //SetMousePosition(GetMouseX() + (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * 16), GetMouseY() + (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) * 16));
        // i have no plans of readding anything similar
    }
    tick_button(&mainmenu->play, (1280 - mainmenu->play.d.x + 10) / 2, 300);
    tick_button(&mainmenu->exit, (1280 - mainmenu->exit.d.x + 10) / 2, 440);
}

void mainmenu_render(MAINMENU* mainmenu)
{
    DrawTexture(default_background, 0, 0, WHITE);
    DrawText("SLIMEY LAND", (1280 - MeasureText("SLIMEY LAND", 144)) / 2, 16, 144, GREEN);
    DrawText("MAN!", 1000, 92, 95, YELLOW);
    DrawText(FormatText("VERSION %s", mainmenu->v_string), 0, 685, 36, WHITE);
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
    draw_button(&mainmenu->b, 1280 + 100, 720 + 100, WHITE, GREEN, BLUE);
    draw_button(&mainmenu->play, (1280 - mainmenu->play.d.x + 10) / 2, 300, WHITE, RED, BLACK);
    draw_button(&mainmenu->exit, (1280 - mainmenu->exit.d.x + 10) / 2, 440, WHITE, RED, BLACK);
    //tick_button(&mainmenu->b, 1280 / 2, 720 / 2);
}
