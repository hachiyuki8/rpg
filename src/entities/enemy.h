#pragma once

#include "../constants/enemy_constants.h"
#include "../globals.h"
#include "object.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <vector>

/*
 * enemy.h
 *
 * This file defines all enemy states and refers to enemy_constants.h.
 *
 */

class Character;

class Enemy {
public:
  Enemy(float xMin, float xMax, float yMin, float yMax,
        MovementState state = MovementState::STILL, int p = ENEMY_HP,
        int diff = ENEMY_DIFFICULTY, float w = ENEMY_WIDTH,
        float h = ENEMY_HEIGHT, int xVBase = ENEMY_XVELOCITY_BASE,
        int yVBase = ENEMY_YVELOCITY_BASE, int xVRange = ENEMY_XVELOCITY_RANGE,
        int yVRange = ENEMY_YVELOCITY_RANGE);
  virtual ~Enemy();

  void print();

  /**
   * @brief Check if the given position collides with enemy
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with enemy collider (not interaction collider)
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief Add given items to enemy's reward list
   *
   * @param o item
   * @param q quantity
   */
  void addReward(Object o, int q);

  /**
   * @brief Check if given position collides with interaction collider
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return bool
   */
  bool isInRange(float x, float y, float w, float h);

  /**
   * @brief When ATTACK is pressed (left mouse button), update enemy HP and
   * state. Caller should ensure player's position collides with enemy first.
   *
   * @param x x position of the player
   * @param attack player's attack attribute
   * @return std::pair<int, int> (difficulty, 1 if alive/0 if killed), (-1, -1)
   * if last attack animation hasn't finished yet
   */
  std::pair<int, int> onAttack(float x, int attack);

  /**
   * @brief Update enemy position, then render based on camera position
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
  Uint32 lastUpdate;

  // enemy position
  float xPos;
  float yPos;
  float width;
  float height;

  // enemy movement state
  MovementState movement;
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

  // enemy movement range, no meaning if movement is STILL
  float xPosMin;
  float xPosMax;
  float yPosMin;
  float yPosMax;

  // enemy properties
  int hp;
  int difficulty; // integer in [0, ENEMY_MAX_DIFFICULTY], 0=doesn't do damage
  std::vector<std::tuple<Object, int>> rewards; // upon being killed

  bool isAttacked = false; // whether or not still in attack animation
  bool isAlive = true;

  // enemy textures with animations
  // in xxxIndices, first value is index of current texture, second value is
  // number of frames it has lasted
  SDL_Texture *stillTexture;
  std::map<Direction, std::vector<SDL_Texture *>> movingTextures;
  std::map<Direction, std::pair<int, int>> movingIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)},
      {Direction::UP, std::make_pair(0, 0)},
      {Direction::DOWN, std::make_pair(0, 0)}};
  // attacking or attacked animation
  std::map<Direction, std::vector<SDL_Texture *>> attackTextures;
  std::map<Direction, std::pair<int, int>> attackIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)}};

  // Calculate damage taken according to player attack and enemy difficulty
  int calculateDamage(int attack);

  // Update enemy position
  void move();

  friend class Character;
};