#pragma once
#include "constants.h"
#include <map>
#include <stdlib.h>

const int SKILLS_SCREEN_WIDTH = 960;
const int SKILLS_SCREEN_HEIGHT = 540;
const int SKILLCARD_ROW = 3;
const int SKILLCARD_COL = 4;
const std::map<int, int> SKILLS_EXP_PER_LEVEL = {{0, 100}, {1, 200}, {2, 400}};
const std::map<std::string, std::pair<std::string, bool>> SKILLS_ALL = {
    {"testing 1", std::make_pair("111", true)},
    {"testing 2", std::make_pair("222", false)},
    {"testing 3", std::make_pair("333", true)},
    {"testing 4", std::make_pair("444", false)},
    {"testing 5", std::make_pair("555", true)}};