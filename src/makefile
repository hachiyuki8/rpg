all: main

main: main.o init.o character.o characterNPC.o enemy.o map.o tile.o teleporter.o object.o inventory.o skills.o stats.o logs.o shop.o help.o convo.o
	clang++ -std=c++20 -g -o main main.o init.o character.o characterNPC.o enemy.o map.o tile.o teleporter.o object.o inventory.o skills.o stats.o logs.o shop.o help.o convo.o -L/opt/homebrew/Cellar/sdl2/2.0.18/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.0.15/lib -L/opt/homebrew/Cellar/sdl2_image/2.0.5/lib -lSDL2 -lSDL2_ttf -lSDL2_image

character.o: entities/character.cpp entities/character.h globals.h constants/character_constants.h constants/controls.h maps/map.h screens/inventory.h screens/skills.h screens/stats.h screens/shop.h screens/logs.h screens/help.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/character.cpp

characterNPC.o: entities/characterNPC.cpp entities/characterNPC.h globals.h constants/npc_constants.h screens/shop.h entities/character.h screens/convo.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/characterNPC.cpp

enemy.o: entities/enemy.cpp entities/enemy.h globals.h constants/enemy_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/enemy.cpp

map.o: maps/map.cpp maps/map.h globals.h constants/constants.h entities/characterNPC.h entities/object.h maps/teleporter.h maps/tile.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 maps/map.cpp

tile.o: maps/tile.cpp maps/tile.h constants/tile_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 maps/tile.cpp

teleporter.o: maps/teleporter.cpp maps/teleporter.h constants/constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 maps/teleporter.cpp

object.o: entities/object.cpp entities/object.h constants/object_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 entities/object.cpp

inventory.o: screens/inventory.cpp screens/inventory.h globals.h constants/inventory_constants.h constants/controls.h entities/object.h screens/logs.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/inventory.cpp

skills.o: screens/skills.cpp screens/skills.h globals.h constants/skills_constants.h screens/logs.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/skills.cpp

stats.o: screens/stats.cpp screens/stats.h globals.h constants/stats_constants.h screens/logs.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/stats.cpp

logs.o: screens/logs.cpp screens/logs.h globals.h constants/logs_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/logs.cpp

shop.o: screens/shop.cpp screens/shop.h globals.h constants/shop_constants.h constants/controls.h entities/character.h entities/object.h screens/logs.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/shop.cpp

help.o: screens/help.cpp screens/help.h globals.h constants/help_constants.h constants/controls.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/help.cpp

convo.o: screens/convo.cpp screens/convo.h globals.h constants/convo_constants.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 screens/convo.cpp

init.o: init.cpp init.h globals.h constants/constants.h constants/controls.h constants/mapfiles.h 
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 init.cpp

main.o: main.cpp init.h globals.h
	clang++ -std=c++20 -g -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 main.cpp

clean:
	rm main *.o