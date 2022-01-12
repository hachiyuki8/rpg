#pragma once

#include "../constants/logs_constants.h"
#include "../globals.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>
#include <iostream>
#include <stdlib.h>

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
  SDL_Texture *texture = UIs[LOGS_TEXTURE];
  TTF_Font *font = fonts[LOGS_FONT];

  int offset = 10;
  float lineHeight;

  std::deque<Log> logs;
};