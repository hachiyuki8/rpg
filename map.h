#pragma once

#include "constants.h"
#include "object.h"
#include "tile.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>

class Map {
public:
  Map(std::vector<SDL_Texture *> tileTextures, float w = SCREEN_WIDTH,
      float h = SCREEN_HEIGHT, float s = TILE_SIZE);
  virtual ~Map();

  void print();
  void addObject(Object o);
  void removeObject(Object o);
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if position collides with an
                                   // unreachable tile or object

  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;

  float width;
  float height;
  float tileSize;
  std::vector<std::vector<Tile>> tiles;
  std::vector<Object> objects;

  friend class Character;
};