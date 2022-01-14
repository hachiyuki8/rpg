#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../assetManager.h"
#include "../constants/controls.h"
#include "../constants/shop_constants.h"
#include "../entities/object.h"
#include "logs.h"

/*
 * shop.h
 *
 * This file defines all shop states and refers to shop_constants.h.
 *
 */

class Character;

class Shop {
 public:
  /**
   * @brief Construct a new shop
   *
   * @param x screen position and dimension
   * @param y
   * @param w
   * @param h
   */
  Shop(float x = (SCREEN_WIDTH - SHOP_SCREEN_WIDTH) / 2,
       float y = (SCREEN_HEIGHT - SHOP_SCREEN_HEIGHT) / 2,
       float w = SHOP_SCREEN_WIDTH, float h = SHOP_SCREEN_HEIGHT);
  virtual ~Shop();

  void print();

  /**
   * @brief Add the gievn item to the shop. If no more space in shop or given
   * item's quantity exceeds the per item limit, no item will be added at all,
   * and will show warnings in terminal since this function is intended to be
   * used for game development intead of the actual gameplay.
   *
   * @param o
   * @param q
   * @return false if failed to add (shop full or quantity exceeds limit)
   */
  bool addItem(Object o, int q);

  /**
   * @brief Open the shop and output instruction to logs
   *
   * @param logs
   */
  void open(Logs *logs);

  /**
   * @brief Close the shop
   *
   */
  void close();

  /**
   * @brief When left mouse button is pressed, select/unselect an item
   *
   * @param x cursor position
   * @param y
   */
  void onClick(float x, float y);

  /**
   * @brief When CONFIRM is pressed, buy one of the selected item if player has
   * enough money and inventory space, and output to logs if successful
   *
   * @param curPlayer
   */
  void onConfirm(Character *curPlayer);

  /**
   * @brief Render the shop screen. This function sets the inventory position
   * attributes for each item in shop.
   * TODO: make it better
   *
   * @param renderer
   */
  void render(SDL_Renderer *renderer);

  static int nextID;

 private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;
  // automatically calculated based on shop layout
  int numRow;
  int numCol;

  // item grouping relies on object names (see operator< in object.h)
  std::map<Object, int> items;
  const Object *curSelected = NULL;

  SDL_Color text_color = SHOP_COLOR;
  SDL_Texture *background = AssetManager::uiTextures[SHOP_BACKGROUND];
  SDL_Texture *texture = AssetManager::uiTextures[SHOP_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[SHOP_FONT][SHOP_FONT_SIZE];
};