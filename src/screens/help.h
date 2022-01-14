#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../assetManager.h"
#include "../constants/help_constants.h"

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
  Help(float x = (SCREEN_WIDTH - HELP_SCREEN_WIDTH) / 2,
       float y = (SCREEN_HEIGHT - HELP_SCREEN_HEIGHT) / 2,
       float w = HELP_SCREEN_WIDTH, float h = HELP_SCREEN_HEIGHT);
  virtual ~Help();

  void init();
  void print();

  void open();
  void close();
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