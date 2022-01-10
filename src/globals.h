#pragma once

#include "constants/constants.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <stdlib.h>
#include <vector>

class CharacterNPC;

class Map;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *mainL_f, *mainM_f, *mainS_f, *mainL_bold_f, *mainM_bold_f,
    *mainS_bold_f;

extern SDL_Texture *startup_t;
extern SDL_Texture *itemlist_t, *skills_t, *stats_t, *logs_t, *shop_t, *help_t,
    *convo_t;
extern SDL_Texture *itemlist_bg, *shop_bg;
extern SDL_Surface *startup_text;

extern std::vector<TTF_Font *> fonts;
extern std::vector<SDL_Texture *> UIs;

// elements in following vectors should only be used by reference
extern SDL_Texture *playerIcon;
extern std::map<Direction, SDL_Texture *> playerStillTextures;
extern std::map<Direction, std::vector<SDL_Texture *>> playerWalkTextures;
extern std::vector<SDL_Texture *> npcTextures;
extern std::vector<SDL_Texture *> tileTextures;
extern std::vector<SDL_Texture *> objectTextures;
extern std::vector<SDL_Texture *> uiTextures;
extern std::map<SDL_Keycode, SDL_Texture *> keyTextures;
extern std::vector<Map *> maps; // each map has Objects, Tiles, and NPCs*
extern std::vector<CharacterNPC *> allNPCs;