#include <scene/Scene.h>
#include <stdbool.h>

extern void (*scene_update)(void* data);
extern void (*scene_render)(void* data);
extern void (*data_f)(void* data);
extern void* scene_data;
extern bool scene_got;
extern int scene_id;

void SetSceneID(int nid)
{
    scene_id = nid;
}

void ChangeScene(void (*update)(void* data), void (*render)(void* data), void* (*data_init)(), void (*data_free)(void* data))
{
    if(scene_got == true)
    {
        data_f(scene_data);
        free(scene_data);
    }
    data_f = data_free;
    scene_data = data_init();
    scene_update = update;
    scene_render = render;
    scene_got = true;
}
