#pragma once

#include "../assetManager.h"
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

// TODO: currently almost exactly the same as Inventory, maybe will consolidate
// these two in the future...
class Shop {
public:
  Shop(float x = (SCREEN_WIDTH - SHOP_SCREEN_WIDTH) / 2,
       float y = (SCREEN_HEIGHT - SHOP_SCREEN_HEIGHT) / 2,
       float w = SHOP_SCREEN_WIDTH, float h = SHOP_SCREEN_HEIGHT);
  virtual ~Shop();

  void print();
  bool addItem(Object o, int q);

  void open(Logs *logs);
  void close();
  void onClick(float x, float y); // select item
  void onConfirm(
      Character
          *curPlayer); // buy one of the selected item, return item value or -1
                       // Character handles the logic of checking if item fits
                       // in the bag; if not, item need to be manually re-added
  void render(SDL_Renderer *renderer); // TODO: make it better

  static int nextID;

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;
  int numRow;
  int numCol;

  const Object *curSelected = NULL;
  std::map<Object, int> items;

  SDL_Color text_color = SHOP_COLOR;
  SDL_Texture *background = AssetManager::uiTextures[SHOP_BACKGROUND];
  SDL_Texture *texture = AssetManager::uiTextures[SHOP_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[SHOP_FONT][SHOP_FONT_SIZE];
};