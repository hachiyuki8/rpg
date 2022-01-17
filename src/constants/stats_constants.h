#pragma once
#include <stdlib.h>

#include <map>

#include "../assetManager.h"
#include "constants.h"

const int STATS_SCREEN_WIDTH = 480;
const int STATS_SCREEN_HEIGHT = 270;
const std::map<int, int> STATS_EXP_PER_LEVEL = {{0, 100}, {1, 200}, {2, 400}};
const std::map<int, int> STATS_HP_PER_LEVEL = {{0, 50}, {1, 100}, {2, 150}};
const std::map<std::string, std::pair<std::string, int>> STATS_ALL_ATTRIBUTES =
    {{"attack", std::make_pair("player attack", 10)},
     {"defense", std::make_pair("player defense", 10)}};
const int STATS_MAX_MONEY = 999999;
const int STATS_MAX_VALUE = 99;

const std::string STATS_TEXTURE = "12_namecard.png";
const std::string STATS_FONT = "1_abaddon_light.ttf";
const int STATS_FONT_SIZE = 18;
const SDL_Color STATS_COLOR = {0, 0, 0};

const int HEALTH_BAR_BG_WIDTH = 150;
const int HEALTH_BAR_BG_HEIGHT = 40;
const int HEALTH_BAR_BG_XPOS = SCREEN_WIDTH - HEALTH_BAR_BG_WIDTH - 20;
const int HEALTH_BAR_BG_YPOS = SCREEN_HEIGHT - HEALTH_BAR_BG_HEIGHT - 20;
const int HEALTH_BAR_WIDTH = 97;
const int HEALTH_BAR_HEIGHT = 17;
const int HEALTH_BAR_XPOS = 40;
const int HEALTH_BAR_YPOS = 12;
const std::string HEALTH_BAR_BG_TEXTURE = "20_healthbarbg.png";
const std::string HEALTH_BAR_TEXTURE = "21_healthbar.png";