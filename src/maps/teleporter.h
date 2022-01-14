#pragma once

#include <SDL.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../constants/constants.h"

class Map;

class Teleporter {
 public:
  Teleporter(Map *src, Map *dest,
             std::map<std::pair<int, int>, std::pair<int, int>> sd);
  virtual ~Teleporter();

  void print();

  static int nextID;

 private:
  int ID;

  Map *src_map;
  Map *dest_map;
  // tile indices in map, must be reachable
  std::map<std::pair<int, int>, std::pair<int, int>> srcToDest;

  friend class Map;
};