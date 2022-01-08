#pragma once

#include "../constants/help_constants.h"
#include "../globals.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <stdlib.h>

struct Control {
  SDL_Keycode key;
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

  float offsetBorder = HELP_OFFSET_BORDER;
  float lineHeight = HELP_LINE_HEIGHT;

  SDL_Color text_color = HELP_COLOR;
  SDL_Texture *texture = UIs[HELP_TEXTURE];
  TTF_Font *font = fonts[HELP_FONT];

  std::map<std::string, Control> controls;
};