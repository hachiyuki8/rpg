#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <vector>

#include "../assetManager.h"
#include "../constants/controls.h"
#include "../constants/inventory_constants.h"
#include "../entities/object.h"
#include "logs.h"

/*
 * inventory.h
 *
 * This file defines all inventory states and refers to inventory_constants.h.
 *
 */

class Inventory {
 public:
  /**
   * @brief Construct a new inventory
   *
   * @param x screen position and dimension
   * @param y
   * @param w
   * @param h
   */
  Inventory(float x = (SCREEN_WIDTH - INVENTORY_WIDTH) / 2,
            float y = (SCREEN_HEIGHT - INVENTORY_HEIGHT) / 2,
            float w = INVENTORY_WIDTH, float h = INVENTORY_HEIGHT);
  virtual ~Inventory();

  void print();

  /**
   * @brief Add the given item to the inventory. If no more space in inventory
   * or given item's quantity exceeds the per item limit, will output to logs
   * and no item will be added at all.
   *
   * @param logs
   * @param o item
   * @param q quantity
   * @return false if failed to add (inventory full or quantity exceeds limit)
   */
  bool addItem(Logs *logs, Object o, int q = 1);

  /**
   * @brief Open the inventory and output instruction to logs
   *
   * @param logs
   */
  void open(Logs *logs);

  /**
   * @brief Close the inventory
   *
   */
  void close();

  /**
   * @brief When a mouse button is pressed, do one of the followings:
   * - left click: select/unselect an item
   * - right click: sell one of the selected item if it's not a QUEST_OBJECT
   *
   * @param logs
   * @param x cursor position
   * @param y
   * @param isLeft true if left click
   * @return value of the item being sold, 0 if doesn't apply
   */
  int onClick(Logs *logs, float x, float y, bool isLeft);

  /**
   * @brief When CONFIRM is pressed, use one of the selected item if applied and
   * output to logs
   *
   * @param logs
   */
  void onConfirm(Logs *logs);

  /**
   * @brief Render the inventory screen. This function sets the inventory
   * position attributes for each item in inventory.
   * TODO: make it better, also use vector instead of map to preserve order?
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
  // automatically calculated based on inventory layout
  int numRow;
  int numCol;

  // item grouping relies on object names (see operator< in object.h)
  std::map<Object, int> items;
  const Object *curSelected = NULL;

  SDL_Color text_color = INVENTORY_COLOR;
  SDL_Texture *background = AssetManager::uiTextures[INVENTORY_BACKGROUND];
  SDL_Texture *texture = AssetManager::uiTextures[INVENTORY_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[INVENTORY_FONT][INVENTORY_FONT_SIZE];

  // Select/unselect items
  void onLeftClick(Logs *logs, float x, float y);

  // If the selected item is not a quest object, decrease its quantity by 1 and
  // return its value, otherwise output to log
  int onRightClick(Logs *logs, float x, float y);

  // Decrease item's quantity by 1, return false if no more remaining
  bool decreaseItem(Object o);
};