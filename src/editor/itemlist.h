#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>

#include <iostream>

#include "constants.h"

class MapEditor;

class Itemlist {
 public:
  Itemlist();
  virtual ~Itemlist();

  static void render(SDL_Renderer *renderer);

 private:
};