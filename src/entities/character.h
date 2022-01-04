#pragma once

#include "../constants/character_constants.h"
#include "../constants/controls.h"
#include "../maps/map.h"
#include "../screens/itemlist.h"
#include "../screens/skills.h"
#include "../screens/stats.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

class Character {
public:
  Character(SDL_Texture *t, SDL_Texture *itemlist_t, SDL_Texture *skills_t,
            SDL_Texture *stats_t, TTF_Font *f, bool isCurrent = false,
            PlayerState state = PlayerState::OTHER_NPC,
            float x = (SCREEN_WIDTH - DEFAULT_CHARACTER_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - DEFAULT_CHARACTER_HEIGHT) / 2,
            float w = DEFAULT_CHARACTER_WIDTH,
            float h = DEFAULT_CHARACTER_HEIGHT,
            float xV = DEFAULT_CHARACTER_XVELOCITY,
            float yV = DEFAULT_CHARACTER_YVELOCITY);
  virtual ~Character();

  void print();
  void showItemlist();
  void showSkills();
  void showStats();
  void pickupObject(); // pick up at most one object

  void interact(); // when INTERACT key is pressed
  void click(float x, float y,
             bool isLeft); // when left or right mouse button is clicked
  void confirm();          // when CONFIRM key is pressed
  bool onInteract(float x, float y, float w, float h); // TO-DO: only for NPCs
  void update(const Uint8 *keys);
  void render(SDL_Renderer *renderer);

  static int nextID;
  Map *curMap;

private:
  int ID;
  Uint32 lastUpdate;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float width;
  float height;
  float xVel;
  float yVel;
  bool isCurPlayer;
  PlayerState playerState;

  UIState uiState = UIState::IN_GAME;
  Itemlist itemlist;
  Skills skills;
  Stats stats;
  // TO-DO: quest screen, map, etc.

  void move(const Uint8 *keys, float dT);
  void renderObjectList(SDL_Renderer *renderer);
  void upgradeSkill(std::string s, int exp);
  void increaseExp(int exp);
  void increaseStat(std::string s, int val);
};