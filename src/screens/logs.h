#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <deque>
#include <iostream>

#include "../assetManager.h"
#include "../constants/logs_constants.h"

struct Log {
  std::string content;
  SDL_Surface *text;
};

class Logs {
 public:
  Logs(float x = 0, float y = SCREEN_HEIGHT - LOGS_SCREEN_HEIGHT,
       float w = LOGS_SCREEN_WIDTH, float h = LOGS_SCREEN_HEIGHT);
  virtual ~Logs();

  void print();
  void addLog(std::string s);
  void toggleShow();

  void render(SDL_Renderer *renderer);

  static int nextID;

 private:
  int ID;
  bool isShowing = true;

  float xPos;
  float yPos;
  float width;
  float height;

  SDL_Color text_color = LOGS_COLOR;
  SDL_Texture *texture = AssetManager::uiTextures[LOGS_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[LOGS_FONT][LOGS_FONT_SIZE];

  int offset = 10;
  float lineHeight;

  std::deque<Log> logs;
};