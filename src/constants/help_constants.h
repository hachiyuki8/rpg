#pragma once
#include "../assetManager.h"
#include "constants.h"
#include "controls.h"
#include <map>

const int HELP_SCREEN_WIDTH = 720;
const int HELP_SCREEN_HEIGHT = 480;
const int HELP_OFFSET_BORDER = 30;
const int HELP_LINE_HEIGHT = 40;
const int HELP_ICON_HEIGHT = 25;

const int NUM_ROW =
    (HELP_SCREEN_HEIGHT - HELP_OFFSET_BORDER * 2) / HELP_LINE_HEIGHT;
const int NUM_COL = 2;

const std::string HELP_TEXTURE = "17_panel9.png";
const std::string HELP_FONT = "0_abaddon_bold.ttf";
const int HELP_FONT_SIZE = 18;
const SDL_Color HELP_COLOR = {0, 0, 0};

const std::map<std::string, SDL_Keycode> HELP_ALL = {
    {"start game", START_GAME},
    {"quit current", QUIT},
    {"move up", UP},
    {"move left", LEFT},
    {"move down", DOWN},
    {"move right", RIGHT},
    {"toggle help page", HELP},
    {"toggle inventory", SHOW_INVENTORY},
    {"toggle skills", SHOW_SKILLS},
    {"toggle player info", SHOW_STATS},
    {"toggle logs screen", SHOW_LOGS},
    {"pick up items", PICKUP_ITEM},
    {"interact/enter new map", INTERACT},
    {"confirm", CONFIRM},
};