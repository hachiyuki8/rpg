#pragma once

#include "entities/character.h"
#include "entities/characterNPC.h"
#include "maps/map.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <vector>

class Map;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *main_font, *second_font;

extern SDL_Texture *startup_t, *player_t;
extern SDL_Texture *itemlist_t, *skills_t, *stats_t, *logs_t, *shop_t;
extern SDL_Surface *startup_text;

// elements in following vectors should only be used by reference
extern std::vector<SDL_Texture *> npcTextures;
extern std::vector<SDL_Texture *> tileTextures;
extern std::vector<SDL_Texture *> objectTextures;
extern std::vector<SDL_Texture *> uiTextures;
extern std::vector<Map> maps; // each map has Objects, Tiles, and NPCs*
extern std::vector<CharacterNPC> NPCs;