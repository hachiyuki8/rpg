#pragma once

#include "../constants/character_constants.h"
#include "../constants/controls.h"
#include "../globals.h"
#include "../maps/map.h"
#include "../screens/help.h"
#include "../screens/itemlist.h"
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

  void init();
  void print();
  bool quit();     // when QUIT key is pressed, return true if game paused
  void showHelp(); // TO-DO
  void showItemlist();
  void showSkills();
  void showStats();
  void showLogs();
  void pickupObject(); // pick up at most one object

  void interact(); // when INTERACT key is pressed
  void click(float x, float y,
             bool isLeft); // when left or right mouse button is clicked
  void confirm();          // when CONFIRM key is pressed
  void update(const Uint8 *keys);
  void render(SDL_Renderer *renderer);

  void testing(); // TO-DO: for testing only

  static int nextID;

  UIState uiState = UIState::IN_GAME;
  Logs logs;
  Map *curMap = NULL;
  Shop *curShop = NULL;             // shop that's currently opened
  CharacterNPC *curConvoNPC = NULL; // NPC that's currently talking to

private:
  int ID;
  Uint32 lastUpdate;

  float xPos;
  float yPos;
  float width;
  float height;
  float xVel;
  float yVel;

  float camX;
  float camY;
  float camW;
  float camH;

  Direction direction = Direction::RIGHT;
  MovementState movementState = MovementState::STILL;
  std::map<Direction, SDL_Texture *> stillTextures;
  std::map<Direction, std::vector<SDL_Texture *>> walkTextures;
  std::map<Direction, std::pair<int, int>> walkIndices = {
      {Direction::LEFT, std::make_pair(0, 0)},
      {Direction::RIGHT, std::make_pair(0, 0)},
      {Direction::UP, std::make_pair(0, 0)},
      {Direction::DOWN,
       std::make_pair(0, 0)}}; // first int is index of current texture, second
                               // int is how many frames it has lasted

  Itemlist itemlist;
  Skills skills;
  Stats stats;
  Help help;

  // TO-DO: quest screen, map, etc.

  void move(const Uint8 *keys, float dT);
  void renderObjectList(SDL_Renderer *renderer);
  void upgradeSkill(std::string s, int exp);
  void increaseExp(int exp);
  void increaseMoney(int m);
  void increaseStat(std::string s, int val);
  void attack(); // when attacking an enemy
  int calculateDamage(int diff);
  void calculateReward(Enemy *e, int diff);

  friend class Shop; // TO-DO: why is this not working
};