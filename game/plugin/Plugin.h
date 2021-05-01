#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdbool.h>
#include <raylib.h>

struct plugin
{
    char* name;
    char* desc;
    bool spawnable;
    float expir;
    Texture tex;
    void* (*init)();
    void (*on_collision)(void* self, void* other);
    void (*update_callback)(void* self, void* game);
    void (*render_callback)(void* self);
};
typedef struct plugin PLUGIN;

void InitCorePlugins();
void CleanPlugins();
void AddPlugin(char* path);
void AddPluginM(char* name, char* desc, bool spawnable, float expir, Texture tex, Texture icon, void (*on_collision)(void* self, void* other), void (*update_callback)(void* self, void* game), void (*render_callback)(void* self), void* (data_init)());
void RemovePlugin(char* name);
PLUGIN* GetPlugin(char* name);

#endif // PLUGIN_H
