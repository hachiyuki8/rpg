#pragma once

#include "../constants/skills_constants.h"
#include "logs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>

struct Skill {
  std::string name;
  std::string description;
  bool isUnlocked = false;
  int curLevel = 0;
  int curExp = 0;
};

struct SkillCard {
  Skill skill;
  bool isSelected = false;
  float xPos = 0;
  float yPos = 0;
  float width = 0;
  float height = 0;

  SDL_Surface *name_text;
  SDL_Surface *description_text;
};

class Skills {
public:
  Skills(float x = (SCREEN_WIDTH - SKILLS_SCREEN_WIDTH) / 2,
         float y = (SCREEN_HEIGHT - SKILLS_SCREEN_HEIGHT) / 2,
         float w = SKILLS_SCREEN_WIDTH, float h = SKILLS_SCREEN_HEIGHT,
         int r = SKILLCARD_ROW, int c = SKILLCARD_COL,
         std::map<int, int> exp = SKILLS_EXP_PER_LEVEL);
  virtual ~Skills();

  void print();
  void initAllSkills(
      std::map<std::string, std::pair<std::string, bool>> sk = SKILLS_ALL);
  void unlockSkill(std::string s);
  void upgradeSkill(Logs *logs, std::string s, int exp);

  void open(Logs *logs);
  void close();
  void onClick(Logs *logs, float x, float y, bool isLeft); // select skill
  void onConfirm(); // TO-DO: maybe allocate skill points?
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

  int numRow;
  int numCol;
  float cardWidth;
  float cardHeight;
  SkillCard *curSelected = NULL;

  SDL_Color text_color = {255, 255, 255};

  std::map<std::string, Skill> skills;
  std::vector<SkillCard> skillcards;
  std::map<int, int> expPerLevel;

  void addSkill(std::string s, std::string d, bool isUnlocked);
  void renderCard(SDL_Renderer *renderer, SkillCard sc);
  void onLeftClick(Logs *logs, float x, float y); // select/unselect
  void onRightClick(Logs *logs, float x,
                    float y); // TO-DO: maybe show description?
};