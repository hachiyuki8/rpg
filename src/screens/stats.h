#pragma once

#include "../constants/stats_constants.h"
#include "../globals.h"
#include "logs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <stdlib.h>

struct Stat {
  std::string name;
  std::string description;
  int value = 0;
  int maxValue = STATS_MAX_VALUE;

  SDL_Surface *name_text;
  SDL_Surface *description_text;
};

class Stats {
public:
  Stats(std::string n = "new player",
        float x = SCREEN_WIDTH - STATS_SCREEN_WIDTH, float y = 0,
        float w = STATS_SCREEN_WIDTH, float h = STATS_SCREEN_HEIGHT);
  virtual ~Stats();

  void print();
  void initAllStats(
      std::map<std::string, std::pair<std::string, int>> st = STATS_ALL);
  void increaseHP(int h);
  void increaseExp(Logs *log, int ex);
  void increaseMoney(Logs *log, int m);
  bool decreaseMoneyIfEnough(Logs *log, int m);
  void increaseStat(Logs *log, std::string s, int val);
  int getStat(std::string s);

  void open();
  void close();
  void render(SDL_Renderer *renderer);
  static int nextID;

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;
  float offsetBorder;
  float offsetLine;
  float offset;

  std::map<int, int> expPerLevel = PLAYER_EXP_PER_LEVEL;
  std::map<int, int> hpPerLevel = PLAYER_HP_PER_LEVEL;

  std::string name;
  int level = 0;
  int exp = 0;
  int money = 0;
  int hp;

  SDL_Color text_color = STATS_COLOR;
  SDL_Texture *texture = UIs[STATS_TEXTURE];
  TTF_Font *font = fonts[STATS_FONT];
  std::map<std::string, Stat> stats;

  void addStat(std::string s, std::string d, int val);

  friend class Character;
};