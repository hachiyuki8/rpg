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
  bool isInvalidPosition(float x, float y, float w, float h);
  void addReward(Object o, int q);

  bool isInRange(float x, float y, float w,
                 float h); // if collides with enemy's interaction range
  std::pair<int, int> onAttack(float x,
                               int attack); // return difficulty & isAlive
  void render(SDL_Renderer *renderer, float camX, float camY, float width,
              float height);

  static int nextID;

private:
  int ID;
  Uint32 lastUpdate;

  // range of movement, no meaning if movement type is STILL
  float xPosMin;
  float xPosMax;
  float yPosMin;
  float yPosMax;

  // current position
  float xPos;
  float yPos;
  float width;
  float height;

  // movement velocity
  int xVel;
  int yVel;
  int xVelBase;
  int xVelRange;
  int yVelBase;
  int yVelRange;

  // textures
  SDL_Texture *stillTexture;
  std::map<Direction, std::vector<SDL_Texture *>> movingTextures;
  std::map<Direction, std::pair<int, int>> movingIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)},
      {Direction::UP, std::make_pair(0, 0)},
      {Direction::DOWN,
       std::make_pair(0, 0)}}; // first int is index of current texture, second
                               // int is how many frames it has lasted
  std::map<Direction, std::vector<SDL_Texture *>>
      attackTextures; // for enemy that doesn't attack, this will be attacked
                      // animation
  std::map<Direction, std::pair<int, int>> attackIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)}};

  int hp;
  int difficulty;
  bool isAttacked = false;
  bool isAlive = true;
  std::vector<std::tuple<Object, int>> rewards;

  MovementState movement;
  Direction xDirection = Direction::RIGHT;
  Direction yDirection = Direction::DOWN;

  int calculateDamage(int attack); // TO-DO: not sure how to calculate it
  void move();

  friend class Character;
};