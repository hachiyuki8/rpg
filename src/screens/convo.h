#pragma once

#include "../constants/convo_constants.h"
#include "../globals.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <tuple>
#include <vector>

struct Line {
  SDL_Texture *icon;
  std::vector<std::string> lines;
  std::vector<SDL_Surface *> line_texts;
};

class Convo {
public:
  Convo(float x = (SCREEN_WIDTH - CONVO_SCREEN_WIDTH) / 2,
        float y = (SCREEN_HEIGHT - CONVO_SCREEN_HEIGHT),
        float w = CONVO_SCREEN_WIDTH, float h = CONVO_SCREEN_HEIGHT);
  virtual ~Convo();

  void print();
  void
  init(std::vector<std::tuple<int, std::vector<std::string>>>
           lines); // int is index into npcTextures or -1 for player texture
  void clear();

  void open();
  void close();
  bool next(); // return false if convo ends
  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;

  float offsetLeft = CONVO_OFFSET_LEFT;
  float border = CONVO_BORDER;
  float iconSize = CONVO_ICON_SIZE;
  float lineHeight = CONVO_LINE_HEIGHT;

  std::vector<Line> allLines;
  int curIndex = 0;

  SDL_Color text_color = CONVO_COLOR;
  SDL_Texture *texture = UIs[CONVO_TEXTURE];
  TTF_Font *font = fonts[CONVO_FONT];
};