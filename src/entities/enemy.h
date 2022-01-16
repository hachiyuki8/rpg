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
 */

class Character;

class Map;

class Enemy {
 public:
  /**
   * @brief Construct a new enemy
   *
   * @param xMin movement range
   * @param xMax
   * @param yMin
   * @param yMax
   * @param n name, should match the folder name containing all textures
   * @param state either IDLE (then position is alwasy (xMin, yMin)) or WALK
   * @param p HP
   * @param diff an integer in [0, ENEMY_MAX_DIFFICULTY], 0=doesn't do damage
   * @param w dimension
   * @param h
   * @param xVBase velocity range
   * @param yVBase
   * @param xVRange
   * @param yVRange
   */
  Enemy(float xMin, float xMax, float yMin, float yMax, std::string n,
        MovementState state = MovementState::IDLE, int p = ENEMY_HP,
        int diff = ENEMY_DIFFICULTY, float w = ENEMY_WIDTH,
        float h = ENEMY_HEIGHT, int xVBase = ENEMY_XVELOCITY_BASE,
        int yVBase = ENEMY_YVELOCITY_BASE, int xVRange = ENEMY_XVELOCITY_RANGE,
        int yVRange = ENEMY_YVELOCITY_RANGE);
  virtual ~Enemy();

  void print();

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
   * @brief Add given items to enemy's reward list
   *
   * @param o item
   * @param q quantity
   */
  void addReward(Object *o, int q);

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
  Uint32 lastUpdate;
  std::string name;

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

  // enemy properties
  int hp;
  int difficulty;
  std::vector<std::tuple<Object *, int>> rewards;  // upon being killed

  // enemy textures with animations
  std::map<MovementState, std::map<Direction, std::vector<SDL_Texture *>>>
      enemyTextures;
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

  // Calculate damage taken according to player attack and enemy difficulty
  int calculateDamage(int attack);

  // Update enemy position if is alive and movement state is WALK
  void move(Map *curMap);

  friend class Character;
  friend class Map;
};