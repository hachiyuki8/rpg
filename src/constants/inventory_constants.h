#pragma once
#include "../assetManager.h"
#include "constants.h"

const int INVENTORY_WIDTH = 610;
const int INVENTORY_HEIGHT = 430;
const int INVENTORY_GRID_SIZE = 50;
const int INVENTORY_BORDER = 10;
const int INVENTORY_OBJECT_SIZE = 30;
const int ITEM_LIMIT = (INVENTORY_WIDTH - INVENTORY_BORDER) /
                       (INVENTORY_GRID_SIZE + INVENTORY_BORDER) *
                       (INVENTORY_HEIGHT - INVENTORY_BORDER) /
                       (INVENTORY_GRID_SIZE + INVENTORY_BORDER);
const int PER_ITEM_LIMIT = 99;  // ideally this number should not be reached

const std::string INVENTORY_TEXTURE = "14_grid3.png";
const std::string INVENTORY_BACKGROUND = "19_panel10.png";
const std::string INVENTORY_FONT = "1_abaddon_light.ttf";
const int INVENTORY_FONT_SIZE = 18;
const SDL_Color INVENTORY_COLOR = {0, 0, 0};