#pragma once

#include "../constants/constants.h"
#include "../entities/characterNPC.h"
#include "../entities/enemy.h"
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
      float h = SCREEN_HEIGHT,
      float s = TILE_SIZE); // mapfile must have dimension (w/s) * (h/s)
  virtual ~Map();

  void print();
  void addTeleporter(Teleporter tp);
  void addObject(Object o);
  void removeObject(Object o);
  void addNPC(CharacterNPC *npc);
  void addEnemy(Enemy *e);
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if position collides with an
                                   // unreachable tile or object
  // check interaction in the following order: NPC->TP->Object, will only
  // carry out one interaction
  std::tuple<Map *, float, float> onInteract(Character *curPlayer, Map *curMap,
                                             float x, float y, float w,
                                             float h);
  std::tuple<int, Enemy *>
  onAttack(int attack, float x, float y, float w,
           float h); // return (-1 if invalid or enemy difficulty, enemy* if
                     // killed or NULL)
  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  static int nextID;

private:
  int ID;

  float width;
  float height;
  float tileSize;
  std::vector<std::vector<Tile>> tiles;
  std::vector<Teleporter> teleporters;
  std::vector<Object> objects;
  std::vector<CharacterNPC *> NPCs;
  std::vector<Enemy *> enemies;

  friend class Character;
};