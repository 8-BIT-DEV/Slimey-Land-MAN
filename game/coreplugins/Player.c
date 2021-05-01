#include <coreplugins/Player.h>
#include <raylib.h>
#include <math.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

extern char spawn_plugins[256][256];
extern Texture spawn_icons[256];
extern int splg_count;

extern Texture noicon;

extern bool sparkles_has;
extern Color sparkle_color;
extern Texture sparkle1;

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

void* player_init()
{
    PLAYER* ply = malloc(sizeof(PLAYER));
    ply->what = 0;
    ply->got = 1;
    ply->use = 0;
    ply->has_sparkles = sparkles_has;
    ply->sparkle_color = sparkle_color;
    for(int i = 0; i < 16; i++)
    {
        ply->effect[i].age = 0;
        ply->effect[i].fall_age = 0;
        ply->effect[i].use = 0;
        ply->effect[i].x = 0;
        ply->effect[i].y = 7;
    }
    return ply;
}

void ply_free(PLAYER* ply)
{
    arraylist_destroy(ply->effect);
}

void ply_target_draw(GAMEOBJECT* self)
{
    PLAYER* ply = self->data;
    if(ply->target.x != 0 || ply->target.y != 0)
    {
        //DrawCircle(ply->target.x, ply->target.y, 8, BLUE);
        DrawCircle(self->x + ply->target.x + 16, self->y + ply->target.y + 16, 8, BLUE);
    }
}

void ply_ui(GAMEOBJECT* self, GAME* game)
{
    PLAYER* ply = self->data;
    Color full_base = BLUE;
    Color non_base = (Color){full_base.r, full_base.g, full_base.b, 160};
    //DrawRectangleRounded((Rectangle){10, 10, 128, 128}, 0.1, 3, full_base);
    //DrawRectangleRounded((Rectangle){154, 10, 128, 128}, 0.1, 3, full_base);
    switch(ply->use)
    {
    case 0:
        DrawRectangleRounded((Rectangle){10, 10, 128, 128}, 0.1, 3, full_base);
        DrawRectangleRounded((Rectangle){154, 10, 128, 128}, 0.1, 3, non_base);
        if(game->in_off != 0) return;
        if(IsGamepadAvailable(0) == false)
        {
            ply->what += GetMouseWheelMove() * -1;
            ply->what = (ply->what < 0) ? 0 : ply->what;
            ply->what = (ply->what > splg_count - 1) ? splg_count - 1 : ply->what;
        }
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) && ply->what < splg_count - 1) ply->what++;
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1) && ply->what > 0) ply->what--;
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_2) || IsMouseButtonPressed(0)) spawn_object(game, spawn_plugins[ply->what], self->x + ply->target.x + 16, self->y + ply->target.y + 16, 0);
        break;
    case 1:
        DrawRectangleRounded((Rectangle){10, 10, 128, 128}, 0.1, 3, non_base);
        DrawRectangleRounded((Rectangle){154, 10, 128, 128}, 0.1, 3, full_base);
        if(game->in_off != 0) return;
        if(IsGamepadAvailable(0) == false)
        {
            ply->got += GetMouseWheelMove() * -1;
            ply->got = (ply->got < 1) ? 1 : ply->got;
            ply->got = (ply->got > game->texcount - 1) ? game->texcount - 1 : ply->got;
        }
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) && ply->got < game->texcount - 1) ply->got++;
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1) && ply->got > 1) ply->got--;
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_2) && self->y + ply->target.y >= 0 || IsMouseButtonPressed(0) && self->y + ply->target.y >= 0) game->map.tiles[((self->y + (int)ply->target.y + 16) / 32)*game->map.width+((self->x + (int)ply->target.x + 16) / 32)] = ply->got;
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && self->y + ply->target.y >= 0 || IsMouseButtonPressed(1) && self->y + ply->target.y >= 0) game->map.tiles[((self->y + (int)ply->target.y + 16) / 32)*game->map.width+((self->x + (int)ply->target.x + 16) / 32)] = 23123198;
        //printf("TILE:%d %d\n", ((self->x + (int)ply->target.x + 16) / 32), ((self->y + (int)ply->target.y + 16) / 32));
        break;
    }
    DrawTextureEx(game->tiletex[ply->got], (Vector2){169, 14}, 0, 3, WHITE);
    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || IsKeyPressed(KEY_ONE)) ply->use = 0;
    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || IsKeyPressed(KEY_TWO)) ply->use = 1;
    //if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) ply->use = 2
    if(splg_count == 0)
    {
        DrawText("No plugins!", 13, (72 / 2), 13, WHITE);
    } else
    {
        //DrawText(FormatText("%d", ply->what), 10, 10, 23, WHITE);
        if(spawn_icons[ply->what].id == 0)
        {
            DrawTextureEx(noicon, (Vector2){25, 14}, 0, 1.5, WHITE);
            DrawText(spawn_plugins[ply->what], 25, 116, 16, WHITE);
        } else
        {
            //DrawTextureRec(spawn_icons[ply->what], (Rectangle){0, 0, 64, 64}, (Vector2){10, 10}, WHITE);
            DrawTextureEx(spawn_icons[ply->what], (Vector2){25, 14}, 0, 1 * (96 / spawn_icons[ply->what].width), WHITE);
            DrawText(spawn_plugins[ply->what], 25, 116, 16, WHITE);
        }
        //if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) && ply->what < splg_count - 1) ply->what++;
        //if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1) && ply->what > 0) ply->what--;
    }
}

void player_update(GAMEOBJECT* self, GAME* game)
{
    PLAYER* ply = self->data;
    ply->game = game;
    Vector2 move = (Vector2){0, 0};
    float mult = 1;
    if(IsKeyDown(KEY_LEFT_SHIFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) mult = 0.5;
    if(IsKeyDown(KEY_LEFT_CONTROL) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) mult = 2;
    if(IsGamepadAvailable(0)) move = (Vector2){GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * GetFrameTime() * 500* mult, GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) * GetFrameTime() * 500 * mult};
    else
    {
        if(IsKeyDown(KEY_W)) move.y = -1 * GetFrameTime() * 500 * mult;
        else if(IsKeyDown(KEY_S)) move.y = 1 * GetFrameTime() * 500 * mult;
        if(IsKeyDown(KEY_A)) move.x = -1 * GetFrameTime() * 500 * mult;
        else if(IsKeyDown(KEY_D)) move.x = 1 * GetFrameTime() * 500 * mult;
    }
    self->x += move.x;
    self->y += move.y;
    Vector2 target = (Vector2){0, 0};
    //printf("FRAME TIME:%f\n", GetFrameTime());
    if(IsGamepadAvailable(0)) target = (Vector2){GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) * 0.016667 * 500, GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) * 0.016667 * 500};
    else
    {
        target = (Vector2){(float)GetMouseX() - 1280 / 2, (float)GetMouseY() - 720 / 2};
        HideCursor();
    }
    //printf("X:%f Y:%f TARGET\n", target.x, target.y);
    if(IsGamepadAvailable(0)) ply->target = (Vector2){target.x * 8, target.y * 10};
    else ply->target = (Vector2){target.x, target.y};
    if(ply->next_timer < ply->next) ply->next_timer += GetFrameTime();
    for(int i = 0; i < 16; i++)
    {
        if(ply->next_timer >= ply->next)
        {
            if(ply->effect[i].use == false)
            {
                ply->next = float_rand(0.4, 1.5);
                printf("SPAWNED PARTICLE %f\n", ply->next_timer);
                ply->next_timer = 0;
                ply->effect[i].use = true;
                ply->effect[i].x = GetRandomValue(0, 32);
                ply->effect[i].y = GetRandomValue(0, 7);
                ply->effect[i].fall_age = float_rand(0.3, 0.5);
                ply->effect[i].age = 0;
            }
        }
        if(ply->effect[i].use == true)
        {
            ply->effect[i].age += GetFrameTime();
            if(ply->effect[i].age >= ply->effect[i].fall_age) ply->effect[i].y += 0.2;
            //ply->effect[i].x += float_rand(-0.5, 0.5);
            if(ply->effect[i].y > 22) ply->effect[i].use = false;
        }
    }
}

void player_render(GAMEOBJECT* self)
{
    PLAYER* ply = self->data;
    GAME* game = ply->game;
    //for(int i = 0; i < 16; i++) if(ply->effect[i].use == true) DrawCircle(self->x + ply->effect[i].x, self->y + ply->effect[i].y, 4, BLUE);
    for(int i = 0; i < 16; i++) if(ply->effect[i].use == true && ply->has_sparkles) DrawTextureEx(sparkle1, (Vector2){self->x + ply->effect[i].x - 4, self->y + ply->effect[i].y - 4}, 0, 2, ply->sparkle_color);
    //DrawCircle(self->x + ply->target.x + 16, self->y + ply->target.y + 16, 8, BLUE);
    //printf("X:%f Y:%f\n", ply->target.x, ply->target.y);
    /*if(ply->target.x != 0 || ply->target.y != 0)
    {
        //DrawCircle(ply->target.x, ply->target.y, 8, BLUE);
        DrawCircle(self->x + ply->target.x + 16, self->y + ply->target.y + 16, 8, BLUE);
    }*/
    /*DrawRectangle(self->area.top.x, self->area.top.y, self->area.top.width, self->area.top.height, GREEN);
    DrawRectangle(self->area.bottom.x, self->area.bottom.y, self->area.bottom.width, self->area.bottom.height, GREEN);
    DrawRectangle(self->area.left.x, self->area.left.y, self->area.left.width, self->area.left.height, PURPLE);
    DrawRectangle(self->area.right.x, self->area.right.y, self->area.right.width, self->area.right.height, PURPLE);*/ // uncomment drawing code to see hitboxes of player
    /*for(int x = self->x / 32 - 4; x < self->x / 32 + 4; x++)
    {
        for(int y = self->y / 32 - 4; y < self->y / 32 + 4; y++)
        {
            if(x > -1 && y > -1)
            {
                if(game->map.tiles[y*game->map.width+x] < 23)
                {
                    Rectangle that = (Rectangle){x * 32, y * 32, 32, 32};
                    if(CheckCollisionRecs(self->area.core, that))
                    {
                        DrawRectangle(x * 32, y * 32, 32, 32, RED);
                    } else
                    {
                        DrawRectangle(x * 32, y * 32, 32, 32, WHITE);
                    }
                }
            }
        }
    }*/
}
