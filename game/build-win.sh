# libtmx libz xml2 libm libdl raylib
# always compile windows version with -D WIN32
# if you want to compile the linux version just open the cb project and press build and run
echo "this shellscript compiles a windows version of Slimey Land MAN"
#CHECK="$1"
#if [ $CHECK == "DEBUG" ]
#then
#echo "RUNNING LIBRARY TESTS"
#x86_64-w64-mingw32-gcc -Iwin-lib -I./ main.c win-lib/raylib.dll -o test_raylib.exe
#exit
#fi
# old compile command doesnt work :(
#x86_64-w64-mingw32-gcc -Wall -Lwin-lib -Iwin-lib -I./ -D WIN32 main.c tokenizer.c dict.c arraylist.c coreplugins/Player.c logging/Logger.c object/Defaults.c plugin/Plugin.c scene/Scene.c scenes/Game.c scenes/MainMenu.c scenes/MapSelect.c ui/Button.c win-lib/dlfcn.c -o win-export/SLM.exe -lraylib -lcrypto -ltmx -lxml2 -lzlibstatic
x86_64-w64-mingw32-gcc -Wall -Lwin-lib -Iwin-lib -I./ -D WIN32 -D CURL_STATICLIB -mwindows win-lib/dlfcn.c main.c gj.c http-get-gen.c arraylist.c dict.c tokenizer.c coreplugins/Player.c coreplugins/Effect.c logging/Logger.c object/Defaults.c plugin/Plugin.c scene/Scene.c scenes/Game.c scenes/MainMenu.c scenes/MapSelect.c ui/Button.c -o win-export/SLM.exe -lm -lraylib -ltmx -lxml2 -lzlibstatic -lcrypto
# x86_64-w64-mingw32-gcc -Wall -Lwin-lib -Iwin-lib -I./ -D WIN32 -D CURL_STATICLIB -mwindows ... -o win-export/SLM.exe -lm -lraylib -ltmx -lxml2 -lzlibstatic -lcurl  -ltmx -lxml2 -lzlibstatic -lcurl -lws2_32 -lnghttp2 -lssh2 -lgsasl -lcrypto -lssl -lz -lwldap32
# win-lib/libtmx.a win-lib/libxml2.a win-lib/libzlibstatic.a
#  -D NGHTTP2_STATIC
echo "BUILT!"
exit

