#pragma once

#include "../assetManager.h"
#include "../constants/controls.h"
#include "../constants/inventory_constants.h"
#include "../entities/object.h"
#include "logs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <vector>

class Inventory {
public:
  Inventory(float x = (SCREEN_WIDTH - INVENTORY_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - INVENTORY_HEIGHT) / 2,
            float w = INVENTORY_WIDTH, float h = INVENTORY_HEIGHT);
  virtual ~Inventory();

  void print();
  void setInteractRange(float left, float right, float up, float down);
  bool addItem(Logs *logs, Object o, int q = 1, bool suppressLog = false);
  void useItem(Object o); // TODO

  void open(Logs *logs);
  void close();
  int onClick(Logs *logs, float x, float y,
              bool isLeft);            // select/sell item, return item value
  void onConfirm(Logs *logs);          // use one of the selected item
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

  SDL_Color text_color = INVENTORY_COLOR;
  SDL_Texture *background = AssetManager::uiTextures[INVENTORY_BACKGROUND];
  SDL_Texture *texture = AssetManager::uiTextures[INVENTORY_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[INVENTORY_FONT][INVENTORY_FONT_SIZE];

  void onLeftClick(Logs *logs, float x, float y); // select/unselect
  int onRightClick(Logs *logs, float x,
                   float y);   // sell one of the selected if not a quest item,
                               // return item value
  bool decreaseItem(Object o); // return false if no more remaining
};