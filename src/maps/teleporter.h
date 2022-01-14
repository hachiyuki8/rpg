#pragma once

#include <SDL.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../constants/constants.h"

/*
 * teleporter.h
 *
 * This file defines all teleporter states.
 *
 */

class Map;

class Teleporter {
 public:
  /**
   * @brief Construct a new teleporter
   *
   * @param src pointer to source map
   * @param dest pointer to destination map
   * @param sd Mappings from a source tile index to a destination tile index.
   * Caller should guarantee that all tile indices are valid with regard to the
   * map (must be reachable tiles).
   */
  Teleporter(Map *src, Map *dest,
             std::map<std::pair<int, int>, std::pair<int, int>> sd);
  virtual ~Teleporter();

  void print();

  static int nextID;

 private:
  int ID;

  Map *src_map;
  Map *dest_map;
  std::map<std::pair<int, int>, std::pair<int, int>> srcToDest;

  friend class Map;
};