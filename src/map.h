#pragma once

#include "constants.h"
#include "object.h"
#include "tile.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

class Map {
public:
  Map(std::vector<SDL_Texture *> tileTextures,
      std::vector<std::vector<int>> mapfile, float w = SCREEN_WIDTH,
      float h = SCREEN_HEIGHT, float s = TILE_SIZE);
  virtual ~Map();

  void print();
  void addObject(Object o);
  void removeObject(Object o);
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if position collides with an
                                   // unreachable tile or object

  // first check if can interact with any teleporters, then with any object,
  // will only carry out one interaction
  void onInteract(float x, float y, float w, float h);
  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;

  float width;
  float height;
  float tileSize;
  std::vector<std::vector<Tile>> tiles;
  std::vector<Object> objects;

  // returns the index of the tile (x, y) is on (in tiles)
  // if on the border of tiles, returns the right and downmost one
  std::pair<int, int> findTileIndex(float x, float y);

  friend class Character;
};