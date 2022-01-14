#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../assetManager.h"
#include "../constants/help_constants.h"

/*
 * help.h
 *
 * This file defines all help page states and refers to help_constants.h.
 *
 */

// Each Control forms a separate entry on the help page. Only one of key or
// mouse field is meaningful depending on isKey.
struct Control {
  bool isKey;
  SDL_Keycode key;
  Uint8 mouse;
  SDL_Surface *name_text;
  int button_width = HELP_ICON_HEIGHT;
  int button_height = HELP_ICON_HEIGHT;
};

class Help {
 public:
  /**
   * @brief Construct a new help page
   *
   * @param x screen position and dimension
   * @param y
   * @param w
   * @param h
   */
  Help(float x = (SCREEN_WIDTH - HELP_SCREEN_WIDTH) / 2,
       float y = (SCREEN_HEIGHT - HELP_SCREEN_HEIGHT) / 2,
       float w = HELP_SCREEN_WIDTH, float h = HELP_SCREEN_HEIGHT);
  virtual ~Help();

  void print();

  /**
   * @brief Initialize the help page content from HELP_KEY and HELP_MOUSE
   *
   */
  void init();

  /**
   * @brief Open the help page
   *
   */
  void open();

  /**
   * @brief Close the help page
   *
   */
  void close();

  /**
   * @brief Render the help page
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

  SDL_Color text_color = HELP_COLOR;
  SDL_Texture *texture = AssetManager::uiTextures[HELP_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[HELP_FONT][HELP_FONT_SIZE];

  std::vector<Control> controls;
};