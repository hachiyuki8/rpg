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
  void setInteractRange(float left, float right, float up, float down);
  bool isInvalidPosition(float x, float y, float w,
                         float h); // invalid if tile is unreachable and
                                   // position collides with tile
  void setTileState(TileState newState);

  // interact if position collides with tile's interaction range
  // if inside = true, only interact when position entirely in tile
  bool onInteract(float x, float y, float w, float h, bool inside = false);
  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float size;
  TileState state;

  // collider for interacting with the tile, default to tile's center point
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  bool isOnTile(float x, float y, float w, float h); // if collides with tile
  bool isInTile(float x, float y, float w, float h); // if entirely in tile
  bool isInTileRange(float x, float y, float w,
                     float h); // if collides with tile's interaction range
};