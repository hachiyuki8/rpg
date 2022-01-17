#pragma once

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <vector>

#include "../assetManager.h"
#include "../constants/enemy_constants.h"
#include "object.h"

/*
 * enemy.h
 *
 * This file defines all enemy states and refers to enemy_constants.h.
 *
 * An enemy encapsulates all information related to the enemy itself
 * (name/texture/rewards/etc.) but contain nothing about the game state
 * (size/position on map/properties that should scale with player level/etc.).
 * The latter is contained in an enemy wrapper.
 *
 * The point of having enemies and enemy wrappers separately is that , with
 * enemies, it is easier to define all types of enemies needed in the game
 * independent of the game state, hence reusing them to create multiple
 * instances. So all enemies should be allocated and managed by AssetManager.
 *
 * But using enemy wrappers, different instances representing the same enemy can
 * each has its own independent game state. An enemy wrapper should be managed
 * by the game state it's dependent on, for example the map.
 *
 */

class Character;

class Map;

class Enemy {
 public:
  /**
   * @brief Construct a new enemy
   *
   * @param n name, should match the folder name containing all textures
   * @param diff an integer in [0, ENEMY_MAX_DIFFICULTY], 0=doesn't do damage
   */
  Enemy(std::string n, int diff = 0);
  virtual ~Enemy();

  void print();

  /**
   * @brief Add given items to enemy's reward list
   *
   * @param o item
   * @param q quantity
   */
  void addReward(Object *o, int q);

  static int nextID;

 private:
  int ID;
  std::string name;

  // enemy properties
  int difficulty;
  std::vector<std::tuple<Object *, int>> rewards;  // upon being killed

  // enemy textures with animations
  std::map<MovementState, std::map<Direction, std::vector<SDL_Texture *>>>
      enemyTextures;
  SDL_Texture *healthbarbg_texture =
      AssetManager::uiTextures[ENEMY_HEALTH_BAR_BG_TEXTURE];
  SDL_Texture *healthbar_texture =
      AssetManager::uiTextures[ENEMY_HEALTH_BAR_TEXTURE];

  friend class Character;
  friend class EnemyWrapper;

  // Calculate damage taken according to player attack and enemy difficulty
  int calculateDamage(int attack);
};

class EnemyWrapper {
 public:
  /**
   * @brief Construct a new enemy wrapper
   *
   * @param e underlying enemy
   * @param xMin movement range
   * @param xMax
   * @param yMin
   * @param yMax
   * @param state either IDLE (then position is alwasy (xMin, yMin)) or WALK
   * @param p full HP (should scale with player level)
   * @param w dimension
   * @param h
   * @param xVBase velocity range
   * @param yVBase
   * @param xVRange
   * @param yVRange
   */
  EnemyWrapper(Enemy *e, float xMin, float xMax, float yMin, float yMax,
               MovementState state = MovementState::IDLE, int p = ENEMY_HP,
               float w = ENEMY_WIDTH, float h = ENEMY_HEIGHT,
               int xVBase = ENEMY_XVELOCITY_BASE,
               int yVBase = ENEMY_YVELOCITY_BASE,
               int xVRange = ENEMY_XVELOCITY_RANGE,
               int yVRange = ENEMY_YVELOCITY_RANGE);
  virtual ~EnemyWrapper();

  void print();

  /**
   * @brief Check if two enemy wrappers are the exact same instance
   *
   * @param ow
   * @return true if enemy wrapper IDs are the same
   */
  bool operator==(const EnemyWrapper &ew) const;

  /**
   * @brief Check if the given position collides with living enemy
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with enemy collider (not interaction collider) and
   * enemy is alive
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief Check if given position collides with interaction collider
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with interaction collider and enemy is alive
   */
  bool isInRange(float x, float y, float w, float h);

  /**
   * @brief When ATTACK is pressed, update enemy HP and state. Caller should
   * ensure player's position collides with enemy first by calling isInRange.
   *
   * @param x x position of the player
   * @param attack player's attack attribute
   * @return (-1, -1) if attack is invalid (enemy dead already or still in last
   * animation), or (enemy difficulty, 1 if alive/0 if killed)
   */
  std::pair<int, int> onAttack(float x, int attack);

  /**
   * @brief Update enemy position, then render based on camera position
   *
   * @param curMap
   * @param renderer
   * @param camX
   * @param camY
   * @param camW
   * @param camH
   */
  void render(Map *curMap, SDL_Renderer *renderer, float camX, float camY,
              float camW, float camH);

  static int nextID;

 private:
  int ID;
  Enemy *enemy;
  Uint32 lastUpdate;

  // enemy position
  float xPos;
  float yPos;
  float width;
  float height;

  // enemy movement state
  MovementState movementState;
  MovementState oldMovementState;  // used to store old value of movement when
                                   // it's changed to ATTACK temporarily
  Direction xDirection = Direction::RIGHT;
  Direction yDirection = Direction::DOWN;
  // everytime direction is changed, velocity randomized to somewhere between
  // base and base+range
  int xVel;
  int yVel;
  int xVelBase;
  int xVelRange;
  int yVelBase;
  int yVelRange;

  // enemy movement range, no meaning if movement is IDLE
  float xPosMin;
  float xPosMax;
  float yPosMin;
  float yPosMax;

  // enemy properties that scale with player level
  int fullHP;
  int curHP;

  // (index of current texture, number of frames it has lasted)
  std::map<MovementState, std::map<Direction, std::pair<int, int>>>
      enemyIndices = {{MovementState::IDLE,
                       {{Direction::LEFT, std::make_pair(0, 0)},
                        {Direction::RIGHT, std::make_pair(0, 0)}}},
                      {MovementState::WALK,
                       {{Direction::LEFT, std::make_pair(0, 0)},
                        {Direction::RIGHT, std::make_pair(0, 0)}}},
                      {MovementState::ATTACK,
                       {{Direction::LEFT, std::make_pair(0, 0)},
                        {Direction::RIGHT, std::make_pair(0, 0)}}},
                      {MovementState::DEATH,
                       {{Direction::LEFT, std::make_pair(0, 0)},
                        {Direction::RIGHT, std::make_pair(0, 0)}}}};

  // Update enemy position if is alive and movement state is WALK
  void move(Map *curMap);

  friend class Map;
};