#pragma once

#include "constants.h"
#include "object.h"
#include "teleporter.h"
#include "tile.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <tuple>
#include <vector>

class Character;

class Map {
public:
  Map(std::vector<SDL_Texture *> tileTextures,
      std::vector<std::vector<int>> mapfile, float w = SCREEN_WIDTH,
      float h = SCREEN_HEIGHT, float s = TILE_SIZE);
  virtual ~Map();

  void print();
  void addTeleporter(Teleporter tp);
  void addObject(Object o);
  void removeObject(Object o);
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if position collides with an
                                   // unreachable tile or object

  // first check if can use any teleporters, then with any object,
  // will only carry out one interaction
  std::tuple<Map *, float, float> onInteract(Map *curMap, float x, float y,
                                             float w, float h);
  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;

  float width;
  float height;
  float tileSize;
  std::vector<std::vector<Tile>> tiles;
  std::vector<Teleporter> teleporters;
  std::vector<Object> objects;
  std::vector<Character *> characters; // TO-DO

  friend class Character;
};