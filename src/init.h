#pragma once

#include "constants/constants.h"
#include "constants/controls.h"
#include "constants/mapfiles.h"
#include "entities/character.h"
#include "entities/characterNPC.h"
#include "entities/object.h"
#include "globals.h"
#include "maps/map.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <vector>

bool init();
void init_fonts();
void init_player_texture();
void init_NPC_texture();
void init_object_texture();
void init_tile_texture();
void init_UI_texture();
void init_key_texture();
void init_maps();
void init_NPCs();