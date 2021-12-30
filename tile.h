#pragma once

#include "constants.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>

class tile {
public:
  tile(SDL_Renderer *renderer = NULL, float x = 0, float y = 0,
       float s = TILE_SIZE, TileStates ts = REACHABLE);
  virtual ~tile();

  void print();
  bool isOnTile(float x, float y, float w, float h); // if collides with tile
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if tile is unreachable and
                                   // position collides with tile
  bool isInTile(float x, float y, float w, float h); // if entirely in tile
  void setTileState(TileStates newState);

  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float size;
  TileStates state;
};