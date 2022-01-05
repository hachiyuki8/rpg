#pragma once

#include "../constants/logs_constants.h"
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
       float w = LOGS_SCREEN_WIDTH, float h = LOGS_SCREEN_HEIGHT,
       int l = LOGS_LINE_LIMIT);
  virtual ~Logs();

  void print();
  void addLog(std::string s);
  void toggleShow();

  void render(SDL_Renderer *renderer);

  static int nextID;
  SDL_Texture *texture; // initialized in Character
  TTF_Font *font;       // initialized in Character

private:
  int ID;
  bool isShowing = true;

  float xPos;
  float yPos;
  float width;
  float height;

  SDL_Color text_color = {255, 255, 255};
  int offset = 10;
  int lineLimit;
  float lineHeight;
  int curSize = 0;

  std::deque<Log> logs;
};