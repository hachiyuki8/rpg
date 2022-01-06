#pragma once

#include "../constants/shop_constants.h"
#include <SDL.h>
#include <iostream>
#include <set>
#include <stdlib.h>

class Shop {
public:
  Shop(float x = (SCREEN_WIDTH - SHOP_SCREEN_WIDTH) / 2,
       float y = (SCREEN_HEIGHT - SHOP_SCREEN_HEIGHT) / 2,
       float w = SHOP_SCREEN_WIDTH, float h = SHOP_SCREEN_HEIGHT,
       float g = SHOP_GRID_SIZE, float o = SHOP_OBJECT_SIZE);
  virtual ~Shop();

  void print();
  void addItem(Object o, int q);
  void sellItem(Logs *logs, Object o);

  void open(Logs *logs);
  void close();
  void onClick(Logs *logs, float x, float y); // select item
  void onConfirm(Logs *logs);                 // buy selected
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

  Object *curSelected = NULL;
}