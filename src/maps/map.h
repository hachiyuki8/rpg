#pragma once

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "../assetManager.h"
#include "../constants/constants.h"
#include "../entities/characterNPC.h"
#include "../entities/enemy.h"
#include "../entities/object.h"
#include "../maps/teleporter.h"
#include "../maps/tile.h"

/*
 * map.h
 *
 * This file defines all map states and refers to map_constants.h.
 *
 */

class Character;

class Map {
 public:
  /**
   * @brief Construct a new map from indices in mapfile. Mapfile should contain
   * the integer index of a tile texture as listed in TILES (as opposed to its
   * string index in tileTextures). A position index refers to a reachable a
   * tile while negative means unreachable.
   *
   * @param mapfile must have dimension (w/s) * (h/s)
   * @param w dimension
   * @param h
   * @param s tile size (must be square)
   */
  Map(std::vector<std::vector<int>> mapfile, float w = SCREEN_WIDTH,
      float h = SCREEN_HEIGHT, float s = TILE_SIZE);
  virtual ~Map();

  void print();

  /**
   * @brief Add the given teleporter to teleporters if associated with this map
   *
   * @param tp
   */
  void addTeleporter(Teleporter tp);

  /**
   * @brief Add the given object to objects
   *
   * @param o
   */
  void addObject(Object o);

  /**
   * @brief Remove the exact instance of the given object from objects. Because
   * object equality is checked by ID, this should always just remove one object
   * because multiple instances of the same object will have different IDs.
   *
   * @param o
   */
  void removeObject(Object o);

  /**
   * @brief Add pointer to the given NPC to NPCs
   *
   * @param npc caller should allocate memory for this
   */
  void addNPC(CharacterNPC *npc);

  /**
   * @brief Add pointer to the given enemy to enemies
   *
   * @param e caller should allocate memory for this
   */
  void addEnemy(Enemy *e);

  /**
   * @brief Check if the given position collides with any unreachable tile,
   * enemy, uncollidable object, or NPC
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with any entity's collider mentioned above
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief When INTERACT is pressed, check possible interaction with any of the
   * map's associated entities in the following order: NPC->teleporter->object.
   * At most one interaction will be carried out.
   *
   * @param curPlayer
   * @param x player position
   * @param y
   * @param w
   * @param h
   * @return potentially updated (map, x pos, y pos) after interaction
   */
  std::tuple<Map *, float, float> onInteract(Character *curPlayer, float x,
                                             float y, float w, float h);

  /**
   * @brief When ATTACK is pressed, check if player is in any living enemies
   * interaction range, if so, that enemy will handle attack event and pass on
   * relevant information for the map to return to the player.
   *
   * @param attack player's attack attribute
   * @param x player position
   * @param y
   * @param w
   * @param h
   * @return First value is -1 if attack is invalid (still in last attack
   * animation or no living enemy in range), or enemy difficulty. Second value
   * is a pointer to the enemy if enemy attacked if killed, or NULL.
   */
  std::tuple<int, Enemy *> onAttack(int attack, float x, float y, float w,
                                    float h);

  /**
   * @brief Render the map and all its entities based on camera position,
   * in the following order: tile->enemies->objects->NPCs
   *
   * @param renderer
   * @param camX
   * @param camY
   * @param camW
   * @param camH
   */
  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  static int nextID;

 private:
  int ID;

  // map dimension
  float width;
  float height;
  float tileSize;

  // map entities
  std::vector<std::vector<Tile>> tiles;
  std::vector<Teleporter> teleporters;
  std::vector<Object> objects;
  std::vector<CharacterNPC *> NPCs;
  std::vector<Enemy *> enemies;

  friend class Character;
};