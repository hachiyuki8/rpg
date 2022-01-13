#pragma once
#include "../assetManager.h"
#include "constants.h"
#include <map>
#include <stdlib.h>

const int SKILLS_SCREEN_WIDTH = 960;
const int SKILLS_SCREEN_HEIGHT = 540;
const int SKILLCARD_ROW = 2;
const int SKILLCARD_COL = 3;
const std::map<int, int> SKILLS_EXP_PER_LEVEL = {{0, 100}, {1, 200}, {2, 400}};
const std::map<std::string, std::pair<std::string, bool>> SKILLS_ALL = {
    {"testing 1",
     std::make_pair(
         "testing testing testing testing testing testing testing testing "
         "testing testing testing testing testing testing testing testing ",
         true)},
    {"testing 2", std::make_pair("222", false)},
    {"testing 3", std::make_pair("333", true)},
    {"testing 4", std::make_pair("444", false)},
    {"testing 5", std::make_pair("555", true)}};

const std::string SKILLS_TEXTURE = "16_grid5.png";
const std::string SKILLS_FONT = "1_abaddon_light.ttf";
const int SKILLS_FONT_SIZE = 18;
const SDL_Color SKILLS_COLOR = {0, 0, 0};