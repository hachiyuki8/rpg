#pragma once

#include "../constants/controls.h"
#include "../constants/itemlist_constants.h"
#include "../entities/object.h"
#include "logs.h"
#include <SDL.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

class Itemlist {
public:
  Itemlist(float x = (SCREEN_WIDTH - ITEMLIST_WIDTH) / 2,
           float y = (SCREEN_HEIGHT - ITEMLIST_HEIGHT) / 2,
           float w = ITEMLIST_WIDTH, float h = ITEMLIST_HEIGHT,
           float g = ITEMLIST_GRID_SIZE, float o = ITEMLIST_OBJECT_SIZE,
           int l = ITEM_LIMIT);
  virtual ~Itemlist();

  void print();
  void addItem(Logs *logs, Object o);
  void useItem(Object o); // TO-DO

  void open(Logs *logs);
  void close();
  int onClick(Logs *logs, float x, float y, bool isLeft); // select/sell item
  void onConfirm(Logs *logs);                             // use selected item
  void render(SDL_Renderer *renderer);

  static int nextID;
  SDL_Texture *texture; // initialized in Character

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;
  float grid_size;
  float object_size;
  int numRow;
  int numCol;

  int limit;
  int curSize = 0;
  Object *curSelected = NULL;
  std::vector<Object> items;

  void onLeftClick(Logs *logs, float x, float y); // select/unselect
  int onRightClick(
      Logs *logs, float x,
      float y); // sell selected if not a quest item, return item value
  void removeItem(Object o);
};