#pragma once
#include <tuple>
#include <vector>

#include "../assetManager.h"
#include "constants.h"
#include "controls.h"

const int HELP_SCREEN_WIDTH = 720;
const int HELP_SCREEN_HEIGHT = 480;
const int HELP_OFFSET_BORDER = 30;
const int HELP_LINE_HEIGHT = 35;
const int HELP_ICON_HEIGHT = 25;

const int HELP_NUM_ROW =
    (HELP_SCREEN_HEIGHT - HELP_OFFSET_BORDER * 2) / HELP_LINE_HEIGHT;
const int HELP_NUM_COL = 2;

const std::string HELP_TEXTURE = "17_panel9.png";
const std::string HELP_FONT = "0_abaddon_bold.ttf";
const int HELP_FONT_SIZE = 18;
const SDL_Color HELP_COLOR = {0, 0, 0};

const std::vector<std::tuple<std::string, SDL_Keycode>> HELP_KEY = {
    std::make_tuple("start game", START_GAME),
    std::make_tuple("pause game", QUIT),
    std::make_tuple("move up", UP),
    std::make_tuple("move left", LEFT),
    std::make_tuple("move down", DOWN),
    std::make_tuple("move right", RIGHT),
    std::make_tuple("toggle help page", HELP),
    std::make_tuple("toggle skills", SHOW_SKILLS),
    std::make_tuple("toggle player info", SHOW_STATS),
    std::make_tuple("toggle logs screen", SHOW_LOGS),
    std::make_tuple("toggle inventory", SHOW_INVENTORY),
    std::make_tuple("use selected in inventory", CONFIRM),
    std::make_tuple("pick up items", PICKUP_ITEM),
    std::make_tuple("enter new map", INTERACT),
    std::make_tuple("interact with NPC or object", INTERACT),
    std::make_tuple("proceed conversation", CONFIRM),
    std::make_tuple("quit conversation", QUIT),
    std::make_tuple("buy selected in shop", CONFIRM),
    std::make_tuple("quit shop", QUIT),
};
const std::vector<std::tuple<std::string, Uint8>> HELP_MOUSE = {
    std::make_tuple("attack", SDL_BUTTON_LEFT),
    std::make_tuple("select/unlect", SDL_BUTTON_LEFT),
    std::make_tuple("sell selected in inventory", SDL_BUTTON_RIGHT),
};