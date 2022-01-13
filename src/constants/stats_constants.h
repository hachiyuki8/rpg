#pragma once
#include "../assetManager.h"
#include "constants.h"
#include <map>
#include <stdlib.h>

const int STATS_SCREEN_WIDTH = 480;
const int STATS_SCREEN_HEIGHT = 270;
const std::map<int, int> PLAYER_EXP_PER_LEVEL = {{0, 100}, {1, 200}, {2, 400}};
const std::map<int, int> PLAYER_HP_PER_LEVEL = {{0, 50}, {1, 100}, {2, 150}};
const std::map<std::string, std::pair<std::string, int>> STATS_ALL = {
    {"attack", std::make_pair("player attack", 10)},
    {"defense", std::make_pair("player defense", 10)}};
const int STATS_MAX_MONEY = 999999;
const int STATS_MAX_VALUE = 99;

const std::string STATS_TEXTURE = "12_namecard.png";
const std::string STATS_FONT = "1_abaddon_light.ttf";
const int STATS_FONT_SIZE = 18;
const SDL_Color STATS_COLOR = {0, 0, 0};