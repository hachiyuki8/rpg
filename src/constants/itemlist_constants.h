#pragma once
#include "../globals.h"
#include "constants.h"

const int ITEMLIST_WIDTH = 480;
const int ITEMLIST_HEIGHT = 360;
const int ITEMLIST_GRID_SIZE = 60;
const int ITEMLIST_OBJECT_SIZE = 40;
const int ITEM_LIMIT = (ITEMLIST_WIDTH / ITEMLIST_GRID_SIZE) *
                       (ITEMLIST_HEIGHT / ITEMLIST_GRID_SIZE);
const int PER_ITEM_LIMIT = 99;
const int ITEMLIST_TEXTURE = 0;
const int ITEMLIST_FONT = 2;
const SDL_Color ITEMLIST_COLOR = {0, 0, 0};