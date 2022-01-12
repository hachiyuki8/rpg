#pragma once

#include "constants/constants.h"
#include "constants/controls.h"
#include "constants/mapfiles.h"
#include "entities/character.h"
#include "entities/characterNPC.h"
#include "entities/enemy.h"
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

/*
 * init.h
 *
 * This file includes initializations of all resources except the player, which
 * is currently done in main.cpp. Most functions return false upon failure.
 *
 * TODO: move player initialization to this file as well
 */

/**
 * Initialize libraries, fonts, and all game assets listed below
 *
 * @return false if any initialization failed
 */
bool init();

// Initialize all fonts in FONTS and store in fonts
bool init_fonts();

// Initialize all textures in PLAYER_LEFT/RIGHT/UP/DOWN and store in
// playerStillTextures and playerWalkTextures
bool init_player_texture();

// Initialize all textures in CHARACTERS and store in npcTextures
bool init_NPC_texture();

// Initialize all textures in OBJECTS and store in objectTextures
bool init_object_texture();

// Initialize all textures in TILES and store in tileTextures
bool init_tile_texture();

// Initialize all textures in UI and store in UIs
bool init_UI_texture();

// Initialize all textures in KEYBOARD and store in keyTextures
bool init_key_texture();

// Create all maps in MAPS from mapfiles.h, manually add objects and
// teleporters, and store in maps
void init_maps();

// Create all NPCs manually and store in allNPCs
void init_NPCs();