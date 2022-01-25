#pragma once

#include <string>
#include <vector>

#include "../constants/asset_constants.h"

const std::string EDITOR_UI_PATH = IMAGE_PATH + "editor/";
const std::vector EDITOR_UIS = {"grid_background.png", "config_background.png"};

const int MAP_EDITOR_SCREEN_WIDTH = 1440;
const int MAP_EDITOR_SCREEN_HEIGHT = 720;

const int MAP_WIDTH = 1080;
const int MAP_HEIGHT = MAP_EDITOR_SCREEN_HEIGHT;
const int MAP_XPOS = 0;
const int MAP_YPOS = 0;

const int ITEMLIST_WIDTH = MAP_EDITOR_SCREEN_WIDTH - MAP_WIDTH;
const int ITEMLIST_HEIGHT = 560;
const int ITEMLIST_XPOS = MAP_WIDTH;
const int ITEMLIST_YPOS = 0;
const int ITEMLIST_GRID_SIZE = 80;
const std::string ITEMLIST_GRID_BG_TEXTURE = "grid_background.png";

const int CONFIG_WIDTH = MAP_EDITOR_SCREEN_WIDTH - MAP_WIDTH;
const int CONFIG_HEIGHT = MAP_EDITOR_SCREEN_HEIGHT - ITEMLIST_HEIGHT;
const int CONFIG_XPOS = MAP_WIDTH;
const int CONFIG_YPOS = ITEMLIST_HEIGHT;
const std::string CONFIG_BG_TEXTURE = "config_background.png";