#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <deque>
#include <iostream>

#include "../assetManager.h"
#include "../constants/logs_constants.h"

/*
 * logs.h
 *
 * This file defines all logs states and refers to logs_constants.h.
 *
 */

struct Log {
  std::string content;
  SDL_Surface *text;
};

class Logs {
 public:
  /**
   * @brief Construct a new logs screen
   *
   * @param x screen position and dimension
   * @param y
   * @param w
   * @param h
   */
  Logs(float x = 0, float y = SCREEN_HEIGHT - LOGS_SCREEN_HEIGHT,
       float w = LOGS_SCREEN_WIDTH, float h = LOGS_SCREEN_HEIGHT);
  virtual ~Logs();

  void print();

  /**
   * @brief Add a new entry to the logs. If number of entries exceeds
   * LOGS_LINE_LIMIT, will discard the oldest entry.
   *
   * @param s content
   */
  void addLog(std::string s);

  /**
   * @brief Open or close the logs screen
   *
   */
  void toggleShow();

  /**
   * @brief Render the logs screen
   *
   * @param renderer
   */
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
  float lineHeight;  // automatically calculated based on offset and line limit

  std::deque<Log> logs;
};