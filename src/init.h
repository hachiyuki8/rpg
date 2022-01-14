#pragma once

#include <vector>

#include "assetManager.h"
#include "constants/mapfiles.h"
#include "entities/character.h"
#include "entities/characterNPC.h"
#include "entities/enemy.h"
#include "entities/object.h"
#include "maps/map.h"

/**
 * @brief Manually create all maps, NPCs, and enemies.
 *
 */
void init();

/**
 * @brief Delete all allocated player, NPCs, enemies and maps
 *
 */
void free();

/**
 * @brief Render the starting screen
 *
 */
void renderStartingScreen();

// Create all maps in MAPS(mapfiles.h), manually add objects and teleporters,
// and store in allMaps
void initMaps();

// Create all NPCs manually and store in allNPCs
void initNPCs();

// Create all enemies manually and store in allEnemies
void initEnemies();

// Create the player and set the initial map
void initPlayer();
