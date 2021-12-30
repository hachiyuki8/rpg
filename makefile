all: main

main: main.o character.o tile.o
	clang++ -o main main.o character.o tile.o -L/opt/homebrew/Cellar/sdl2/2.0.18/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.0.15/lib -lSDL2 -lSDL2_ttf

character.o: character.cpp
	clang++ -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 character.cpp

tile.o: tile.cpp
	clang++ -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 tile.cpp

main.o: main.cpp constants.h
	clang++ -c -I/opt/homebrew/Cellar/sdl2/2.0.18/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.15/include/SDL2 main.cpp

clean:
	rm main *.o