#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <map>

#include "../init.h"
#include "constants.h"
#include "itemlist.h"

class MapEditor {
 public:
  MapEditor();
  virtual ~MapEditor();

  static bool init();

  static void quit();

  static void render();

  inline static SDL_Window *window;
  inline static SDL_Renderer *renderer;
  inline static std::map<std::string, SDL_Texture *> editorTextures;
  inline static std::map<std::string, SDL_Texture *> objectTextures;
  inline static std::map<std::string, SDL_Texture *> tileTextures;

  // texture name (index into AssetManager/MapEditor::objectTextures) -> index
  // into AssetManager::allObjects
  inline static std::map<std::string, int> allObjectsIndex;
  // TODO: grid positions

 private:
  inline static Itemlist itemlist;

  static bool initTextures_EditorUI();
  static bool initTextures_Object();
  static bool initTextures_Tile();
};