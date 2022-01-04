#pragma once
#include "constants.h"
#include <map>
#include <stdlib.h>

const int STATS_SCREEN_WIDTH = 960;
const int STATS_SCREEN_HEIGHT = 540;
const std::map<int, int> PLAYER_EXP_PER_LEVEL = {{0, 100}, {1, 200}, {2, 400}};
const std::map<std::string, std::pair<std::string, int>> STATS_ALL = {
    {"attack", std::make_pair("player attack", 0)},
    {"defense", std::make_pair("player defense", 0)}};
const int STATS_MAX_MONEY = 999999;
const int STATS_MAX_VALUE = 99;