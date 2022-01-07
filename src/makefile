all: main

main: main.o init.o character.o characterNPC.o map.o tile.o teleporter.o object.o itemlist.o skills.o stats.o logs.o shop.o
	clang++ -std=c++20 -g -o main main.o init.o character.o characterNPC.o map.o tile.o teleporter.o object.o itemlist.o skills.o stats.o logs.o shop.o -L/opt/homebrew/Cellar/sdl2/2.0.18/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.0.15/lib -L/opt/homebrew/Cellar/sdl2_image/2.0.5/lib -lSDL2 -lSDL2_ttf -lSDL2_image

character.o: entities/character.cpp entities/character.h constants/character_constants.h constants/controls.h screens/itemlist.h maps/map.h screens/skills.h screens/stats.h screens/logs.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/character.cpp

characterNPC.o: entities/characterNPC.cpp entities/characterNPC.h constants/character_constants.h screens/shop.h entities/character.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/characterNPC.cpp

map.o: maps/map.cpp maps/map.h constants/constants.h entities/object.h maps/teleporter.h maps/tile.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 maps/map.cpp

tile.o: maps/tile.cpp maps/tile.h constants/tile_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 maps/tile.cpp

teleporter.o: maps/teleporter.cpp maps/teleporter.h constants/constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 maps/teleporter.cpp

object.o: entities/object.cpp entities/object.h constants/object_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/object.cpp

itemlist.o: screens/itemlist.cpp screens/itemlist.h constants/itemlist_constants.h entities/object.h constants/controls.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/itemlist.cpp

skills.o: screens/skills.cpp screens/skills.h constants/skills_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/skills.cpp

stats.o: screens/stats.cpp screens/stats.h constants/stats_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/stats.cpp

logs.o: screens/logs.cpp screens/logs.h constants/logs_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/logs.cpp

shop.o: screens/shop.cpp screens/shop.h constants/shop_constants.h entities/object.h constants/controls.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/shop.cpp

init.o: init.cpp init.h constants/constants.h constants/controls.h constants/mapfiles.h globals.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 init.cpp

main.o: main.cpp init.h globals.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 main.cpp

clean:
	rm main *.o