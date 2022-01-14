#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <tuple>
#include <vector>

#include "../assetManager.h"
#include "../constants/convo_constants.h"

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
  void init(
      std::vector<std::tuple<std::string, std::vector<std::string>>>
          lines);  // string is index into npcTextures or "" for player texture
  void clear();

  void open();
  void close();
  bool next();  // return false if convo ends
  void render(SDL_Renderer *renderer);

  static int nextID;

 private:
  int ID;
  bool isShowing = false;

  float xPos;
  float yPos;
  float width;
  float height;

  std::vector<Line> allLines;
  int curIndex = 0;

  SDL_Color text_color = CONVO_COLOR;
  SDL_Texture *texture = AssetManager::uiTextures[CONVO_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[CONVO_FONT][CONVO_FONT_SIZE];
};