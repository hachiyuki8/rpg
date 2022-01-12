#pragma once

#include "../constants/skills_constants.h"
#include "../globals.h"
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
         std::map<int, int> exp = SKILLS_EXP_PER_LEVEL);
  virtual ~Skills();

  void print();
  void initAllSkills(); // SKILLS_ALL
  void unlockSkill(std::string s);
  void upgradeSkill(Logs *logs, std::string s, int exp);

  void open();
  void close();
  void onClick(float x, float y, bool isLeft); // select skill
  void onConfirm(); // TO-DO: maybe allocate skill points?
  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;

  float cardWidth;
  float cardHeight;
  SkillCard *curSelected = NULL;

  SDL_Color text_color = SKILLS_COLOR;
  SDL_Texture *texture = UIs[SKILLS_TEXTURE];
  TTF_Font *font = fonts[SKILLS_FONT];

  std::map<std::string, Skill> skills;
  std::vector<SkillCard> skillcards;
  std::map<int, int> expPerLevel;

  void addSkill(std::string s, std::string d, bool isUnlocked);
  void renderCard(SDL_Renderer *renderer, SkillCard sc);
  void onLeftClick(float x, float y);  // select/unselect
  void onRightClick(float x, float y); // TO-DO
};