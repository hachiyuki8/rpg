#pragma once

#include "constants.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>

class Map;

class Teleporter {
public:
  Teleporter(Map *src, Map *dest, int src_r, int src_c, int dest_r, int dest_c);
  virtual ~Teleporter();

  void print();

  static int nextID;

private:
  int ID;

  Map *src_map;
  Map *dest_map;
  // tile index in map, must be reachable
  int src_row;
  int src_col;
  int dest_row;
  int dest_col;

  friend class Map;
};