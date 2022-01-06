#pragma once

#include "../constants/controls.h"
#include "../constants/shop_constants.h"
#include "../entities/object.h"
#include "logs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>

class Character;

// TO-DO: currently almost exactly the same as Itemlist, maybe will consolidate
// these two in the future...
class Shop {
public:
  Shop(float x = (SCREEN_WIDTH - SHOP_SCREEN_WIDTH) / 2,
       float y = (SCREEN_HEIGHT - SHOP_SCREEN_HEIGHT) / 2,
       float w = SHOP_SCREEN_WIDTH, float h = SHOP_SCREEN_HEIGHT,
       float g = SHOP_GRID_SIZE, float o = SHOP_OBJECT_SIZE,
       int pl = SHOP_PER_ITEM_LIMIT);
  virtual ~Shop();

  void print();
  bool addItem(Object o, int q);

  void open(Logs *logs);
  void close();
  void onClick(Logs *logs, float x, float y); // select item
  void onConfirm(
      Character
          *curPlayer); // buy one of the selected item, return item value or -1
                       // Character handles the logic of checking if item fits
                       // in the bag; if not, item need to be manually re-added
  void render(SDL_Renderer *renderer);

  static int nextID;
  SDL_Texture *texture; // initialized in CharacterNPC
  TTF_Font *font;       // initialized in Character

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

  int perLimit;
  const Object *curSelected = NULL;
  std::map<Object, int> items;

  SDL_Color text_color = {0, 0, 0};
};