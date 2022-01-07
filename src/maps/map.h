#pragma once

#include "../constants/constants.h"
#include "../entities/characterNPC.h"
#include "../entities/object.h"
#include "../globals.h"
#include "../maps/teleporter.h"
#include "../maps/tile.h"
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
  Map(std::vector<std::vector<int>> mapfile, float w = SCREEN_WIDTH,
      float h = SCREEN_HEIGHT, float s = TILE_SIZE);
  virtual ~Map();

  void print();
  void addTeleporter(Teleporter tp);
  void addObject(Object o);
  void removeObject(Object o);
  void addNPC(CharacterNPC *npc);
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if position collides with an
                                   // unreachable tile or object

  // first check if can interact with any NPC, then use any teleporters, then
  // with any object, will only carry out one interaction
  std::tuple<Map *, float, float> onInteract(Character *curPlayer, Map *curMap,
                                             float x, float y, float w,
                                             float h);
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
  std::vector<CharacterNPC *> NPCs; // TO-DO

  friend class Character;
};