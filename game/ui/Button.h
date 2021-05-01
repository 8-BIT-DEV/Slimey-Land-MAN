#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <raylib.h>

struct button
{
    int got_button;
    char* text;
    Texture tex;
    bool use_tex;
    Vector2 d;
    void (*callback)(void* args);
    void* callback_arg;
};
typedef struct button BUTTON;

BUTTON create_button(char* text, bool use_texture, Texture tex, Vector2 size, void(*callback)(void* args), void* callback_arg);
void draw_button(BUTTON* button, int x, int y, Color col1, Color col2, Color col3);
void tick_button(BUTTON* button, int x, int y);

#endif // BUTTON_H
