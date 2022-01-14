#pragma once

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

#include "../constants/tile_constants.h"

class Tile {
 public:
  Tile(SDL_Texture *t, float x = 0, float y = 0, float s = TILE_SIZE,
       TileState ts = TileState::REACHABLE);
  virtual ~Tile();

  void print();
  bool isInvalidPosition(float x, float y, float w,
                         float h);  // invalid if tile is unreachable and
                                    // position collides with tile
  void setTileState(TileState newState);
  bool isInTile(float x, float y, float w,
                float h);  // if collides with tile center

  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  static int nextID;

 private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float size;
  TileState state;

  bool isOnTile(float x, float y, float w, float h);  // if collides with tile

  friend class Map;
};