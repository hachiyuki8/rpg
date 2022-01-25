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

/**
 * @brief If in game mode, create all objects manually and store in
 * AssetManager::allObjects. If in editor mode, manually store the texture name
 * and index into AssetManager::allObjects in MapEditor::allObjectsIndex for
 * those objects that should show up in map editor.
 *
 * Note that each unique item should ideally only be associated with one object
 * and has a unique name. If multiple instances of different sizes/positions are
 * needed, use object wrappers and initialize them after maps. See object.h for
 * more.
 *
 * @param isGameMode
 *
 */
void initObjects(bool isGameMode = true);

/**
 * @brief Create all enemies manually and store in allEnemies.
 *
 * Note that each unique enemy should ideally only be associated with one enemy
 * and has a unique name. If multiple instances of different
 * sizes/positions/movement types/HPs are needed, use enemy wrappers and
 * initialize tham after maps. See enemy.h for more.
 *
 */
void initEnemies();

/**
 * @brief Create all maps in MAPS(mapfiles.h), manually add objects and enemies
 * (using wrappers), and teleporters, and store in allMaps.
 *
 * TODO: Each enemy wrapper needs to be initialized at a valid position,
 * otherwise will get stuck. Teleporters must also be pointing to valid
 * positions. Maybe one day I will improve this.
 *
 */
void initMaps();

/**
 * @brief Create all NPCs manually and store in allNPCs
 *
 */
void initNPCs();

/**
 * @brief Create the player and set the initial map. Note that player must be
 * initialized at a valid position.
 */
void initPlayer();
