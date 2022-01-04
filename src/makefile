all: main

main: main.o character.o map.o tile.o teleporter.o object.o itemlist.o skills.o stats.o
	clang++ -std=c++20 -o main main.o character.o map.o tile.o teleporter.o object.o itemlist.o skills.o stats.o -L/opt/homebrew/Cellar/sdl2/2.0.18/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.0.15/lib -lSDL2 -lSDL2_ttf

character.o: character.cpp character.h character_constants.h controls.h itemlist.h map.h skills.h stats.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 character.cpp

map.o: map.cpp map.h constants.h object.h teleporter.h tile.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 map.cpp

tile.o: tile.cpp tile.h tile_constants.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 tile.cpp

teleporter.o: teleporter.cpp teleporter.h constants.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 teleporter.cpp

object.o: object.cpp object.h object_constants.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 object.cpp

itemlist.o: itemlist.cpp itemlist.h itemlist_constants.h object.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 itemlist.cpp

skills.o: skills.cpp skills.h skills_constants.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 skills.cpp

stats.o: stats.cpp stats.h stats_constants.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 stats.cpp

main.o: main.cpp constants.h controls.h mapfiles.h
	clang++ -std=c++20 -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 main.cpp

clean:
	rm main *.o