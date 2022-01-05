#pragma once

#include "../constants/stats_constants.h"
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
        float x = (SCREEN_WIDTH - STATS_SCREEN_WIDTH) / 2,
        float y = (SCREEN_HEIGHT - STATS_SCREEN_HEIGHT) / 2,
        float w = STATS_SCREEN_WIDTH, float h = STATS_SCREEN_HEIGHT,
        std::map<int, int> exp = PLAYER_EXP_PER_LEVEL);
  virtual ~Stats();

  void print();
  void initAllStats(
      std::map<std::string, std::pair<std::string, int>> st = STATS_ALL);
  void increaseExp(Logs *log, int ex);
  void increaseMoney(Logs *log, int m);
  void increaseStat(Logs *log, std::string s, int val);

  void open();
  void close();
  void render(SDL_Renderer *renderer);
  static int nextID;
  SDL_Texture *texture; // initialized in Character
  TTF_Font *font;       // initialized in Character

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;
  float offset = 60;

  std::string name;
  int level = 0;
  int exp = 0;
  int money = 0;
  std::map<int, int> expPerLevel;

  SDL_Color text_color = {0, 0, 0};
  std::map<std::string, Stat> stats;

  void addStat(std::string s, std::string d, int val);
};