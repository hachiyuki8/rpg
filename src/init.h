#pragma once

#include "assetManager.h"
#include "constants/mapfiles.h"
#include "entities/character.h"
#include "entities/characterNPC.h"
#include "entities/enemy.h"
#include "entities/object.h"
#include "maps/map.h"
#include <vector>

/**
 * @brief Manually create all maps, NPCs, and enemies.
 *
 */
void init();

// Create all maps in MAPS(mapfiles.h), manually add objects and teleporters,
// and store in allMaps
void initMaps();

// Create all NPCs manually and store in allNPCs
void initNPCs();

// Create all enemies manually and store in allEnemies
void initEnemies();