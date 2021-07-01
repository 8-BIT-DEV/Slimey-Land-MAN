# Compilers needed
Slimey Land MAN is compiled using gcc for its native platform of linux and uses mingw for the windows port. So you'll need to use the same compilers as the target platform. Do not use i686 on mingw! Only 86_64.

# Flags needed
Below is A list of flags to compile A Slimey Land MAN plugin. A * represents an argument to the flag. If the flag is followed by A $ it repeats. If the flag is followed by A ! it is optinal. If it is followed by A : it is required and should appear once.
- -fPIC : required
- -shared : to create A shared library
- -I* : path to slm dev kit headers
- -I* ! path to UI header(s)
- -I* ! path to your own header(s)
- *.c $ your C files
- -o *.(so)(dll) : The output file for your plugin so for linux and dll for windows

# Compiler statement
Using the list above the below command can be used as A template. Replace the compiler used by the one you are using.
```
gcc -fPIC -shared -Islimeyland\!\ dev\ kit\ v2/headers/ pluginmain.c -o plugin.c
```

# Where to put plugins
All plugins go into res/plugins/ but A custom plugin loader might load from some where else. If you want to use custom assets in your plugin you can make A copy of the res directoy and delete all the assets in your copy then paste in your plugin in the plugins direcyory of your copy then you can put your other assets  in the other directorys. Only plugins go in the plugins directory! Following the instructions above someone can just merge your res directory with the games res directory and your plugin will be installed.
