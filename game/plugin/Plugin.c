#include <plugin/Plugin.h>
#include <dict.h>

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <dlfcn.h>

// coreplugins
#include <coreplugins/Player.h>
#include <coreplugins/Test.h>
#include <object/Defaults.h>
#include <raylib.h>

extern char* version_string;

char plugin_names[1024][256];
int plg_count = 0;

char spawn_plugins[1024][256];
Texture spawn_icons[1024];
int splg_count = 0;

dict_t* plugins;
Texture noicon;

void* handles[1024];
int handles_count = 0;

void InitCorePlugins()
{
    noicon = LoadTexture("res/textures/misc/noicon.png");
    plugins = malloc(sizeof(dict_t));
    dict_init(plugins);
    AddPluginM("Player", "YAY!!!!", false, -1, LoadTexture("res/textures/entity/player.png"), LoadTexture("res/textures/entity/player.png"), NULL, player_update, player_render, player_init);
    AddPluginM("My plugin", "does nothing", true, 10, LoadTexture("res/textures/default/plaster.png"), LoadTexture("res/textures/entity/playerrrr.png"), NULL, test_update, NULL, test_init);
    AddPluginM("effect_system", "does effects", true, -1, LoadTexture("dsdada"), LoadTexture("dawdadwda"), NULL, effect_update, effect_render, effect_init);
    //AddPlugin("res/plugins/plugin.so");
    DIR* dir;
    struct dirent* file;
    dir = opendir("res/plugins/");
    while((file = readdir(dir)) != NULL)
    {
        #ifdef WIN32
        printf("GOT:%s WIN_UNSUPPORTED_VALUE\n", file->d_name);
        #else
        printf("GOT:%s %d\n", file->d_name, file->d_type);
        #endif // WIN32
        if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
        {
            char* path = strdup("res/plugins/");
            strcat(path, file->d_name);
            AddPlugin(path);
            free(path);
        }
    }
    closedir(dir);
}

void CleanPlugins()
{
    for(int i = 0; i < plg_count; i++)
    {
        void* data = GetPlugin(plugin_names[i]);
        free(data);
        data = NULL;
        printf("CLEANED PLUGIN : %s\n", plugin_names[i]);
    }
    for(int i = 0; i < handles_count; i++)
    {
        printf("CLOSED PLUGIN HANDLE WITH ID:%d\n", i);
        void (*freefree)() = dlsym(handles[i], "freefree");
        freefree();
        dlclose(handles[i]);
    }
}

void FUUCKOFF()
{
    printf("huiwerhjgfyergfrgyufgweiufguyfgyu34fg3y4ugfu34ygf\n\\n\n\\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void AddPlugin(char* path)
{
    void* handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    void (*get_links)(char* links[]) = dlsym(handle, "getlinks");
    void (*loadcallbacks)(void (*so)(), void (*dso)(), void (*apm)(), void (*rp)(), void (*gp)(), void (*se)()) = dlsym(handle, "loadcallbacks");
    char* (*get_v)() = dlsym(handle, "get_version");
    char* pv = get_v();
    if(strcmp(pv, version_string) != 0)
    {
        printf("PLUGIN IS EITHER TOO OLD OR TOO NEW %s\n", path);
        printf("PLUGIN VERSION %s GAME VERSION %s", pv, version_string);
        dlclose(handle);
        return;
    }
    char* links[256];
    get_links(links);
    int i = 0;
    while(links[i] != NULL)
    {
        dlsym(handle, links[i]);
        i++;
    }
    void (*init)() = dlsym(handle, "initinit");
    loadcallbacks(spawn_object, despawn_object, AddPluginM, RemovePlugin, GetPlugin, spawn_effect);
    init();
    handles[handles_count] = handle;
    handles_count++;
}

void AddPluginM(char* name, char* desc, bool spawnable, float expir, Texture tex, Texture icon, void (*on_collision)(void* self, void* other), void (*update_callback)(void* self, void* game), void (*render_callback)(void* self), void* (data_init)())
{
    if(spawnable == true)
    {
        strcpy(spawn_plugins[splg_count], name);
        spawn_icons[splg_count] = icon;
        splg_count++;
    }
    strcpy(plugin_names[plg_count], name);
    PLUGIN* plg = malloc(sizeof(PLUGIN));
    plg->name = name;
    plg->desc = desc;
    plg->spawnable = spawnable;
    plg->expir = expir;
    plg->tex = tex;
    plg->on_collision = on_collision;
    plg->update_callback = update_callback;
    plg->render_callback = render_callback;
    plg->init = data_init;
    dict_set(plugins, name, plg);
    plg_count++;
}

void RemovePlugin(char* name)
{
    void* data = GetPlugin(name);
    free(data);
    dict_del(plugins, name);
}

PLUGIN* GetPlugin(char* name)
{
    PLUGIN* data;
    dict_get(plugins, name, &data);
    return data;
}
