#pragma once

#include "constants.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>

class Tile {
public:
  Tile(SDL_Texture *t, float x = 0, float y = 0, float s = TILE_SIZE,
       TileState ts = TileState::REACHABLE);
  virtual ~Tile();

  void print();
  bool isOnTile(float x, float y, float w, float h); // if collides with tile
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if tile is unreachable and
                                   // position collides with tile
  bool isInTile(float x, float y, float w, float h); // if entirely in tile
  void setTileState(TileState newState);

  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float size;
  TileState state;
};