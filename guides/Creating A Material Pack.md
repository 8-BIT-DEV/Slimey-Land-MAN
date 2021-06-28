# Creating A Material Pack
SLM uses materials to allow maps to have different looks instead of just the default.

## Texture formatting
Textures used as tiles in SLM should be 32x32 although in the future higher resolution textures may be supported. The textures should be stored in there own sub-directory in the textures directory named by the name of the material pack.

## Configuration file formatting
A material pack is nothing more than A collection of textures without A .int file. A configuration file begins with the number of textures/tiles. The default material pack starts with A "23". Then A space and the path to A texture is put. When creating the TILED tileset add them in the same order they appear in the configuration file. Below is an example .int file. The ID 0 is reserved for the player spawn as such use the default player spawn texture.

```
4 res/textures/default/player_spawn.png res/textures/default/sand.png res/textures/default/sandstone.png res/textures/default/test_mat.png
```

This will create A material pack with 3 textures sand sandstone and test_mat.

## Notes
- Paths to textures cannot have spaces
- When A map sets the name of the material pack it is formatted "matpackname".int
- The limit of textures in A material pack is 256 but because of the player spawn tile it is 255.
- There are plans to allow shaders to see which material pack is in use.
