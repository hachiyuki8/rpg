#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <vector>

#include "../assetManager.h"
#include "../constants/skills_constants.h"
#include "logs.h"

/*
 * skills.h
 *
 * This file defines all skills screen states and refers to skill_constants.h.
 *
 */

struct Skill {
  std::string name;
  std::string description;
  bool isUnlocked = false;
  int curLevel = 0;
  int curExp = 0;
};

// Skills screen consists of SkillCards, each of which associated with a Skill
struct SkillCard {
  Skill skill;
  bool isSelected = false;
  // position and dimension in skills screen
  float xPos = 0;
  float yPos = 0;
  float width = 0;
  float height = 0;

  SDL_Surface *name_text;
  SDL_Surface *description_text;
};

class Skills {
 public:
  /**
   * @brief Construct a new skills screen
   *
   * @param x screen position and dimension
   * @param y
   * @param w
   * @param h
   * @param exp EXP needed for each level
   */
  Skills(float x = (SCREEN_WIDTH - SKILLS_SCREEN_WIDTH) / 2,
         float y = (SCREEN_HEIGHT - SKILLS_SCREEN_HEIGHT) / 2,
         float w = SKILLS_SCREEN_WIDTH, float h = SKILLS_SCREEN_HEIGHT,
         std::map<int, int> exp = SKILLS_EXP_PER_LEVEL);
  virtual ~Skills();

  void print();

  /**
   * @brief Initialize all skills from SKILLS_ALL by adding them to skills and
   * skillcards
   *
   */
  void initAllSkills();

  /**
   * @brief Unlock a skill if it exists
   *
   * @param s skill name
   */
  void unlockSkill(std::string s);

  /**
   * @brief Increase a skill's EXP by the given amount (non-negative only) if it
   * exists and is unlocked. If max level reached, output to logs.
   *
   * @param logs
   * @param s skill name
   * @param exp
   */
  void upgradeSkill(Logs *logs, std::string s, int exp);

  /**
   * @brief Open the skills screen
   *
   */
  void open();

  /**
   * @brief Close the skills screen
   *
   */
  void close();

  /**
   * @brief When a mouse button is pressed, do one of the followings:
   * - left click: select/unselect a skill
   * - right click: TODO
   *
   * @param x cursor position
   * @param y
   * @param isLeft
   */
  void onClick(float x, float y, bool isLeft);

  /**
   * @brief Render the skills screen, showing all unlocked skills
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

  // automatically calculated based on width/height and SKILLCARD_ROW/COL
  float cardWidth;
  float cardHeight;
  SkillCard *curSelected = NULL;

  SDL_Color text_color = SKILLS_COLOR;
  SDL_Texture *texture = AssetManager::uiTextures[SKILLS_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[SKILLS_FONT][SKILLS_FONT_SIZE];

  std::map<std::string, Skill> skills;
  std::vector<SkillCard> skillcards;
  std::map<int, int> expPerLevel;  // EXP needed for each level

  // Add the given skill to skills and skillcards if it doesn't exist already by
  // initializing a Skill and SkillCard object
  void addSkill(std::string s, std::string d, bool isUnlocked);

  // Render a SkillCard with skill name, description, and level
  void renderCard(SDL_Renderer *renderer, SkillCard sc);

  // Select/unselect a skill
  void onLeftClick(float x, float y);

  // TODO: currently no-op
  void onRightClick(float x, float y);
};