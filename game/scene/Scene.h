#ifndef SCENE_H
#define SCENE_H

void SetSceneID(int nid);
void ChangeScene(void (*update)(void* data), void (*render)(void* data), void* (*data_init)(), void (*data_free)(void* data));

#endif // SCENE_H
