# Basics of plugins
In SLM plugins have 4 mandatory functions in A plugin they are "init", "initinit", "getlinks" and "freefree". They server the function of initialization and freeing of the plugin.

### void init();
Is called before initinit. Where you can add shared functions, add objects and set extra scene functions.

### void initinit();
Called after all plugins have been loaded allowing retrieval of shared functions without worrying about whether the plugin sharing them has loaded yet.

### void freefree();
Called when the plugin is freed used to free/unload memory/other.

### void getlinks(char* links[256]);
getlinks is passed an array of char*. You set each index to A function name that you want dlsym to be called on then at the end of the list place A NULL terminator.

# Utils header
The current utils version as of now is v3 but this may change in the future. It contains the handle variable for runtime function linking and all functions for loading the function pointers to game functions. It also specifies the version number that this utils is meant for use with. Version numbers do not include pre-releases. It go's shift.major.minor-ext. "ext" represents things like "rc1" or "preview".

# Example code

```C
#include <slm-utils-v3.h>

struct my_object
{
	float value;
};
typedef struct my_object obj;

void* object_init()
{
	obj* o = malloc(sizeof(obj));
	o->value = 0.01;
	return o;
}

void object_update(GAMEOBJECT* self, GAME* game)
{
	obj* o = self->data;
	o->value += 0.02;
	self->x += o->value;
}

void object_render(GAMEOBJECT* self)
{
	// does nothing
	// you can pass NULL if you dont render anything in here
	// but this is here as an example
}

void getlinks(char* links[256])
{
	links[0] = "object_init";
	links[1] = "object_update";
	links[2] = "object_render";
	links[3] = NULL;
}

void init()
{
	// the update/render function argument can be NULL
	AddPluginM("My object", "Its an object", true, -1, LoadTexture("default-tex-here.png"), LoadTexture("icon-here.png"), NULL, object_update, object_render, object_init);
}

void initinit()
{
}

void freefree()
{
}
```

AddPluginM is the function used for registering objects its prototype is below

```C
void AddPluginM(char* name, char* desc, bool spawnable, float expir, Texture tex, Texture icon, void (*on_collision)(void* self, void* other), void (*update_callback)(void* self, void* game), void (*render_callback)(void* self), void* (data_init)());
```

# Notes
- You can find more in the Plugin Utils guide.
- It is not needed to free the objects you register.
- You can pass non-constant strings to "name" and "desc" allowing for changing names and descriptions.
