#pragma once

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

#include "../constants/tile_constants.h"

/*
 * tile.h
 *
 * This file defines all tile states and refers to tile_constants.h.
 *
 */

class Tile {
 public:
  /**
   * @brief Construct a new tile
   *
   * @param t tile texture
   * @param x position on map
   * @param y
   * @param s tile size
   * @param ts tile state
   */
  Tile(SDL_Texture *t, float x = 0, float y = 0, float s = TILE_SIZE,
       TileState ts = TileState::REACHABLE);
  virtual ~Tile();

  void print();

  /**
   * @brief Check if the given position collides with tile when it shouldn't
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if tile is unreachable and position collides with tile
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief Modify tile state
   *
   * @param newState
   */
  void setTileState(TileState newState);

  /**
   * @brief Check if the given position covers the tile center. This is used for
   * deciding if teleporter should be triggered.
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with tile center
   */
  bool isInTile(float x, float y, float w, float h);

  /**
   * @brief Render the tile based on camaera position
   *
   * @param renderer
   * @param camX
   * @param camY
   * @param camW
   * @param camH
   */
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

  // Return true if given position collides with tile
  bool isOnTile(float x, float y, float w, float h);

  friend class Map;
};