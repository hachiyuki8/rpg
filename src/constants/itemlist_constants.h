#pragma once
#include "../globals.h"
#include "constants.h"

const int ITEMLIST_WIDTH = 610;
const int ITEMLIST_HEIGHT = 430;
const int ITEMLIST_GRID_SIZE = 50;
const int ITEMLIST_BORDER = 10;
const int ITEMLIST_OBJECT_SIZE = 30;
const int ITEM_LIMIT = (ITEMLIST_WIDTH - ITEMLIST_BORDER) /
                       (ITEMLIST_GRID_SIZE + ITEMLIST_BORDER) *
                       (ITEMLIST_HEIGHT - ITEMLIST_BORDER) /
                       (ITEMLIST_GRID_SIZE + ITEMLIST_BORDER);
const int PER_ITEM_LIMIT = 99;
const int ITEMLIST_TEXTURE = 0;
const int ITEMLIST_BACKGROUND = 7;
const int ITEMLIST_FONT = 2;
const SDL_Color ITEMLIST_COLOR = {0, 0, 0};