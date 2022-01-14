#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../assetManager.h"
#include "../constants/stats_constants.h"
#include "logs.h"

/*
 * stats.h
 *
 * This file defines all stats screen states and refers to stats_constants.h.
 *
 */

struct Attribute {
  std::string name;
  std::string description;
  int value = 0;
  int maxValue = STATS_MAX_VALUE;

  SDL_Surface *name_text;
  SDL_Surface *description_text;
};

class Stats {
 public:
  /**
   * @brief Construct a new stats screen
   *
   * @param n player name
   * @param x screen position
   * @param y
   * @param w
   * @param h
   */
  Stats(std::string n = "new player",
        float x = SCREEN_WIDTH - STATS_SCREEN_WIDTH, float y = 0,
        float w = STATS_SCREEN_WIDTH, float h = STATS_SCREEN_HEIGHT);
  virtual ~Stats();

  void print();

  /**
   * @brief Initialize player HP (at level 0) and all attributes from
   * STATS_ALL_ATTRIBUTES by adding them to attributes. Note that player level,
   * EXP, HP and money are stored separately and don't count as part of
   * attributes.
   *
   */
  void initAllStats();

  /**
   * @brief Change player HP by the given amount. If positive amount, cap at
   * max HP of current level.
   * TODO: If negative amount, do something when HP <= 0
   *
   * @param h
   */
  void increaseHP(int h);

  /**
   * @brief Increase player EXP by the given amount (non-negative only) and
   * update player level if necessary. If max level reached, output to logs.
   *
   * @param log
   * @param ex
   */
  void increaseExp(Logs *log, int ex);

  /**
   * @brief Increase player money by the given amount (non-negative only). If
   * STATS_MAX_MONEY reached, output to logs.
   *
   * @param log
   * @param m
   */
  void increaseMoney(Logs *log, int m);

  /**
   * @brief Decrease player money by the given amount (non-negative only). If
   * not enough money, output to logs and player money won't be changed.
   *
   * @param log
   * @param m
   * @return false if not enough money
   */
  bool decreaseMoneyIfEnough(Logs *log, int m);

  /**
   * @brief Increase a player attribute by the given amount (non-negative only)
   * if exists. If max value reached, output to logs.
   *
   * @param log
   * @param s attribute name
   * @param val
   */
  void increaseAttribute(Logs *log, std::string s, int val);

  /**
   * @brief Return the value of the given player attribute if it exists
   *
   * @param s attribute name
   * @return attribute value or -1 if doesn't exist
   */
  int getAttribute(std::string s);

  /**
   * @brief Open the stats screen
   *
   */
  void open();

  /**
   * @brief Close the stats screen
   *
   */
  void close();

  /**
   * @brief Render the stats screen, showing player level, EXP, HP, money, and
   * all attributes
   *
   * @param renderer
   */
  void render(SDL_Renderer *renderer);

  static int nextID;

 private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;

  // automatically calculated based on width/height
  float offsetBorder;
  float offsetLine;
  float offset;

  std::string name;
  int level = 0;
  int exp = 0;
  int money = 0;
  int hp;
  std::map<std::string, Attribute> attributes;
  // EXP and HP needed for each level
  std::map<int, int> expPerLevel = PLAYER_EXP_PER_LEVEL;
  std::map<int, int> hpPerLevel = PLAYER_HP_PER_LEVEL;

  SDL_Color text_color = STATS_COLOR;
  SDL_Texture *texture = AssetManager::uiTextures[STATS_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[STATS_FONT][STATS_FONT_SIZE];

  // Add the given attribute to attributes if it doesn't exist already by
  // initializing an Attribute object
  void addAttribute(std::string s, std::string d, int val);

  friend class Character;
};