#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <tuple>
#include <vector>

#include "../assetManager.h"
#include "../constants/character_constants.h"
#include "../constants/controls.h"
#include "../maps/map.h"
#include "../screens/help.h"
#include "../screens/inventory.h"
#include "../screens/logs.h"
#include "../screens/skills.h"
#include "../screens/stats.h"

/*
 * character.h
 *
 * This file defines all player states and refers to character_constants.h.
 *
 */

class Shop;

class Character {
 public:
  /**
   * @brief Construct a new character
   *
   * @param x position
   * @param y
   * @param w dimension
   * @param h
   * @param xV velocity
   * @param yV
   */
  Character(float x = (SCREEN_WIDTH - CHARACTER_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - CHARACTER_HEIGHT) / 2,
            float w = CHARACTER_WIDTH, float h = CHARACTER_HEIGHT,
            float xV = CHARACTER_XVELOCITY, float yV = CHARACTER_YVELOCITY);
  virtual ~Character();

  void print();

  /**
   * @brief Initialize player stats, skills, help, and add initial log
   *
   */
  void init();

  /**
   * @brief When QUIT is pressed, do one of the followings depending on uiState:
   * - quit the current conversation (progress lost)
   * - close the current shop
   * - pause the game
   *
   * @return true if game is paused
   */
  bool quit();

  /**
   * @brief When HELP is pressed, toggle the help page
   *
   */
  void showHelp();

  /**
   * @brief When SHOW_INVENTORY is pressed, toggle inventory
   *
   */
  void showInventory();

  /**
   * @brief When SHOW_SKILLS is pressed, toggle skills screen
   *
   */
  void showSkills();

  /**
   * @brief When SHOW_STATS is pressed, toggle player statistics
   *
   */
  void showStats();

  /**
   * @brief When SHOW_LOGS is pressed, toggle logs screen
   *
   */
  void showLogs();

  /**
   * @brief When PICKUP_ITEM is pressed, pick up at most one object in range,
   * increase money if the object is money, otherwise add to inventory if
   * there's space
   *
   */
  void pickupObject();

  /**
   * @brief When INTERACT is pressed, carry out at most one interaction with
   * assets on the current map (NPC/teleporter/items), may result in map change
   *
   */
  void interact();

  /**
   * @brief When left or right mouse button is pressed, do one of the followings
   * depending on uiState:
   * - select/unselect/sell items in inventory
   * - select/unselect items in shop
   * - select/unselect skills
   * - attack an enemy in range
   *
   * @param x cursor position
   * @param y
   * @param isLeft true if left click
   */
  void click(float x, float y, bool isLeft);

  /**
   * @brief When CONFIRM is pressed, do one of the followings depending on
   * uiState:
   * - sell one selected item in inventory
   * - buy one selected item in shop
   * - proceed the current conversation
   *
   */
  void confirm();

  /**
   * @brief Check if the given position collides with the player
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with player collider (not interaction collider)
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief Update player position according to current keyboard state
   *
   * @param keys
   */
  void update(const Uint8 *keys);

  /**
   * @brief Render the current map and player based on camera position, and any
   * open UI screens
   *
   * @param renderer
   */
  void render(SDL_Renderer *renderer);

  void testing();  // TODO: for testing only

  static int nextID;

  UIState uiState = UIState::IN_GAME;
  Logs logs;
  Map *curMap = NULL;
  CharacterNPC *curNPC = NULL;  // current NPC interacting with

 private:
  int ID;
  Uint32 lastUpdate;

  // player position
  float xPos;
  float yPos;
  float width;
  float height;

  // player movement states
  float xVel;
  float yVel;
  Direction direction = Direction::RIGHT;
  MovementState movementState = MovementState::IDLE;

  // camera position, centered on player when possible
  float camX;
  float camY;
  float camW;
  float camH;

  // player assets
  Inventory inventory;
  Skills skills;
  Stats stats;
  Help help;
  // TODO: quest screen, map, etc.

  // player textures with animations
  std::map<MovementState, std::map<Direction, std::vector<SDL_Texture *>>>
      playerTextures = {{MovementState::IDLE,
                         AssetManager::playerTextures[MovementState::IDLE]},
                        {MovementState::WALK,
                         AssetManager::playerTextures[MovementState::WALK]},
                        {MovementState::ATTACK,
                         AssetManager::playerTextures[MovementState::ATTACK]}};
  // (index of current texture, number of frames it has lasted)
  std::map<MovementState, std::map<Direction, std::pair<int, int>>>
      playerIndices = {{MovementState::IDLE,
                        {{Direction::LEFT, std::make_pair(0, 0)},
                         {Direction::RIGHT, std::make_pair(0, 0)},
                         {Direction::UP, std::make_pair(0, 0)},
                         {Direction::DOWN, std::make_pair(0, 0)}}},
                       {MovementState::WALK,
                        {{Direction::LEFT, std::make_pair(0, 0)},
                         {Direction::RIGHT, std::make_pair(0, 0)},
                         {Direction::UP, std::make_pair(0, 0)},
                         {Direction::DOWN, std::make_pair(0, 0)}}},
                       {MovementState::ATTACK,
                        {{Direction::LEFT, std::make_pair(0, 0)},
                         {Direction::RIGHT, std::make_pair(0, 0)},
                         {Direction::UP, std::make_pair(0, 0)},
                         {Direction::DOWN, std::make_pair(0, 0)}}}};

  // Update player position, then the camera position and movement states
  void move(const Uint8 *keys, float dT);

  // Upgrade the skill with the given name if it exists and is unlocked
  void upgradeSkill(std::string s, int exp);

  // Increase player EXP
  void increaseExp(int exp);

  // Increase player money
  void increaseMoney(int m);

  // Increase player statistic with the given name if it exists
  void increaseStat(std::string s, int val);

  // Update player HP when attacking, and get rewards if enemy killed
  void attack();

  // Calculate damage taken according to enemy difficulty and player statistics
  int calculateDamage(int diff);

  // Calculate EXP and money reward based on enemy difficulty
  void calculateStatsReward(Enemy *e, int diff);

  friend class Shop;  // TODO: why is this not working
};