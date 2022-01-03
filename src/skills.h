#pragma once

#include "constants.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <stdlib.h>

struct Skill {
  std::string name;
  bool isUnlocked = false;
  int curLevel = 0;
  int curExp = 0;
};

class Skills {
public:
  Skills(float x = (SCREEN_WIDTH - SKILLS_SCREEN_WIDTH) / 2,
         float y = (SCREEN_HEIGHT - SKILLS_SCREEN_HEIGHT) / 2,
         float w = SKILLS_SCREEN_WIDTH, float h = SKILLS_SCREEN_HEIGHT,
         std::map<int, int> exp = SKILLS_EXP_PER_LEVEL);
  virtual ~Skills();

  void print();
  void initAllSkills(std::map<std::string, bool> sk = SKILLS_ALL);
  void unlockSkill(std::string s);
  void upgradeSkill(std::string s, int exp);

  // TO-DO
  void open();
  void close();
  void render(SDL_Renderer *renderer);

  static int nextID;
  SDL_Texture *texture; // initialized in Character

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;

  std::map<std::string, Skill> skills;
  std::map<int, int> expPerLevel;

  void addSkill(std::string s, bool isUnlocked);
};