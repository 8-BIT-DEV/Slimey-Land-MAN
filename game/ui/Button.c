#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>

#include <ui/Button.h>

BUTTON create_button(char* text, bool use_texture, Texture tex, Vector2 size, void(*callback)(void* args), void* callback_arg)
{
    BUTTON new;
    new.text = text;
    new.d = size;
    new.callback_arg = callback_arg;
    new.callback = callback;
    new.got_button = 0;
    new.tex = tex;
    new.use_tex = use_texture;
    return new;
}

void draw_button(BUTTON* button, int x, int y, Color col1, Color col2, Color col3)
{
    switch(button->use_tex)
    {
    case false:
        DrawRectangle(x - 10, y - 10, button->d.x + 10, button->d.y + 10, col1);
        DrawRectangle(x, y, button->d.x - 10, button->d.y - 10, col2);
        DrawText(button->text, (x - 5) + (button->d.x - MeasureText(button->text, 40)) / 2, y - 20 + (button->d.y / 2), 40, col3);
        break;
    case true:
        DrawTextureEx(button->tex, (Vector2){x, y}, 0, 1 * (button->d.x / button->tex.width), WHITE);
        break;
    }
}

void tick_button(BUTTON* button, int x, int y)
{
    Rectangle rect = (Rectangle){x - 10, y - 10, button->d.x + 10, button->d.y + 10};
    //DrawRectangle(rect.x, rect.y, rect.width, rect.height, (Color){255, 100, 100, 127});
    if(CheckCollisionPointRec((Vector2){GetMouseX(), GetMouseY()}, rect) && IsMouseButtonPressed(0))
    {
        button->callback(button->callback_arg);
    }
}
