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

/*
 * convo.h
 *
 * This file defines all conversation states and refers to convo_constants.h.
 *
 */

// Each Line forms a separate page of a conversation. It can have multiple lines
// of sentences but should all come from the same speaker.
struct Line {
  SDL_Texture *icon;
  std::vector<std::string> lines;
  std::vector<SDL_Surface *> line_texts;
};

class Convo {
 public:
  /**
   * @brief Construct a new conversation screen
   *
   * @param x screen position and dimension
   * @param y
   * @param w
   * @param h
   */
  Convo(float x = (SCREEN_WIDTH - CONVO_SCREEN_WIDTH) / 2,
        float y = (SCREEN_HEIGHT - CONVO_SCREEN_HEIGHT),
        float w = CONVO_SCREEN_WIDTH, float h = CONVO_SCREEN_HEIGHT);
  virtual ~Convo();

  void print();

  /**
   * @brief Initialize the conversation content from the input
   *
   * @param lines Each element is (speaker texture name, lines to be shown on
   * that page), where texture name is a string index (key) into npcTextures or
   * "" for player icon.
   */
  void init(
      std::vector<std::tuple<std::string, std::vector<std::string>>> lines);

  /**
   * @brief Delete all content of the current conversation and free the surfaces
   *
   */
  void clear();

  /**
   * @brief When the conversation is opened, always start from the first page
   *
   */
  void open();

  /**
   * @brief Close the conversation (progress lost if not finished)
   *
   */
  void close();

  /**
   * @brief Proceed to the next page of the conversation. If the end is reached,
   * automatically close the conversation.
   *
   * @return false if conversation eneded
   */
  bool next();

  /**
   * @brief Render the conversation screen and the current conversation content
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

  std::vector<Line> allLines;  // each element is a page in the conversation
  int curIndex = 0;  // current conversation progress (index into allLines)

  SDL_Color text_color = CONVO_COLOR;
  SDL_Texture *texture = AssetManager::uiTextures[CONVO_TEXTURE];
  TTF_Font *font = AssetManager::allFonts[CONVO_FONT][CONVO_FONT_SIZE];
};