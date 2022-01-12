#pragma once

#include "../constants/controls.h"
#include "../constants/itemlist_constants.h"
#include "../entities/object.h"
#include "../globals.h"
#include "logs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <vector>

class Itemlist {
public:
  Itemlist(float x = (SCREEN_WIDTH - ITEMLIST_WIDTH) / 2,
           float y = (SCREEN_HEIGHT - ITEMLIST_HEIGHT) / 2,
           float w = ITEMLIST_WIDTH, float h = ITEMLIST_HEIGHT);
  virtual ~Itemlist();

  void print();
  void setInteractRange(float left, float right, float up, float down);
  bool addItem(Logs *logs, Object o, int q);
  void useItem(Object o); // TO-DO

  void open(Logs *logs);
  void close();
  int onClick(Logs *logs, float x, float y,
              bool isLeft);            // select/sell item, return item value
  void onConfirm(Logs *logs);          // use one of the selected item
  void render(SDL_Renderer *renderer); // TO-DO: make it better

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

  SDL_Color text_color = ITEMLIST_COLOR;
  SDL_Texture *background = UIs[ITEMLIST_BACKGROUND];
  SDL_Texture *texture = UIs[ITEMLIST_TEXTURE];
  TTF_Font *font = fonts[ITEMLIST_FONT];

  void onLeftClick(Logs *logs, float x, float y); // select/unselect
  int onRightClick(Logs *logs, float x,
                   float y);   // sell one of the selected if not a quest item,
                               // return item value
  bool decreaseItem(Object o); // return false if no more remaining
};