#pragma once

#include "../constants/character_constants.h"
#include "../constants/controls.h"
#include "../globals.h"
#include "../maps/map.h"
#include "../screens/help.h"
#include "../screens/inventory.h"
#include "../screens/logs.h"
#include "../screens/skills.h"
#include "../screens/stats.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <tuple>
#include <vector>

/*
 * character.h
 *
 * This file defines all player states and refers to character_constants.h.
 *
 */

class Shop;

class Character {
public:
  Character(float x = (SCREEN_WIDTH - DEFAULT_CHARACTER_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - DEFAULT_CHARACTER_HEIGHT) / 2,
            float w = DEFAULT_CHARACTER_WIDTH,
            float h = DEFAULT_CHARACTER_HEIGHT,
            float xV = DEFAULT_CHARACTER_XVELOCITY,
            float yV = DEFAULT_CHARACTER_YVELOCITY);
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
   * @param x cursor x position
   * @param y cursor y position
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

  void testing(); // TODO: for testing only

  static int nextID;

  UIState uiState = UIState::IN_GAME;
  Logs logs;
  Map *curMap = NULL;
  Shop *curShop = NULL;             // shop that's currently opened
  CharacterNPC *curConvoNPC = NULL; // NPC that's currently talking to

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
  MovementState movementState = MovementState::STILL;

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
  // in xxxIndices, first value is index of current texture, second value is
  // number of frames it has lasted
  std::map<Direction, SDL_Texture *> stillTextures;
  std::map<Direction, std::vector<SDL_Texture *>> walkTextures;
  std::map<Direction, std::pair<int, int>> walkIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)},
      {Direction::UP, std::make_pair(0, 0)},
      {Direction::DOWN, std::make_pair(0, 0)}};
  std::map<Direction, std::vector<SDL_Texture *>> attackTextures;
  std::map<Direction, std::pair<int, int>> attackIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)},
      {Direction::UP, std::make_pair(0, 0)},
      {Direction::DOWN, std::make_pair(0, 0)}};

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

  // Calculate rewards based on enemy difficulty
  void calculateReward(Enemy *e, int diff);

  friend class Shop; // TODO: why is this not working
};