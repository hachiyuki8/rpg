#pragma once

#include "constants.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>

class character {
public:
  character(SDL_Renderer *renderer = NULL,
            float x = (SCREEN_WIDTH - DEFAULT_CHARACTER_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - DEFAULT_CHARACTER_HEIGHT) / 2,
            float w = DEFAULT_CHARACTER_WIDTH,
            float h = DEFAULT_CHARACTER_HEIGHT,
            float xV = DEFAULT_CHARACTER_XVELOCITY,
            float yV = DEFAULT_CHARACTER_YVELOCITY);
  virtual ~character();

  void print();

  void onEntry();
  void onExit();
  void update(const Uint8 *keys);
  void render(SDL_Renderer *renderer);

  SDL_Texture *texture;
  static int nextID;

private:
  int ID;
  Uint32 lastUpdate;

  float xPos;
  float yPos;
  float width;
  float height;
  float xVel;
  float yVel;

  void move(const Uint8 *keys, float dT);
};