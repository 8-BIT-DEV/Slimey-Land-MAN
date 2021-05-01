#ifndef MAINMENU_H
#define MAINMENU_H

#include <ui/Button.h>

struct mainmenu
{
    char v_string[256];
    char* splash;
    float splash_timer;
    BUTTON b;
    BUTTON play;
    BUTTON exit;
};
typedef struct mainmenu MAINMENU;

void* mainmenu_init();
void mainmenu_free(MAINMENU* mainmenu);
void mainmenu_update(MAINMENU* mainmenu);
void mainmenu_render(MAINMENU* mainmenu);

#endif // MAINMENU_H
