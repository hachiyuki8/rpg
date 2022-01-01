#pragma once

#include "constants.h"
#include "map.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

class Character {
public:
  Character(SDL_Texture *t, SDL_Texture *itemlist_t, bool flag = false,
            float x = (SCREEN_WIDTH - DEFAULT_CHARACTER_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - DEFAULT_CHARACTER_HEIGHT) / 2,
            float w = DEFAULT_CHARACTER_WIDTH,
            float h = DEFAULT_CHARACTER_HEIGHT,
            float xV = DEFAULT_CHARACTER_XVELOCITY,
            float yV = DEFAULT_CHARACTER_YVELOCITY);
  virtual ~Character();

  void print();
  void addObject(Object o);
  void removeObject(Object o);
  void showObjects();
  void pickupObject(Map *map); // pick up at most one object

  void interact(Map *map); // when INTERACT key is pressed
  bool onInteract(float x, float y, float w, float h); // TO-DO: only for NPCs
  void update(const Uint8 *keys, Map *curMap);
  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  Uint32 lastUpdate;
  SDL_Texture *texture, *itemlist_texture;

  float xPos;
  float yPos;
  float width;
  float height;
  float xVel;
  float yVel;
  bool isCurPlayer;
  bool isShowingObjects;
  std::vector<Object> objects;

  void move(const Uint8 *keys, float dT, Map *curMap);
  void renderObjectList(SDL_Renderer *renderer);
};