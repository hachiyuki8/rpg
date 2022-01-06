#pragma once
#include <SDL.h>
#include <map>
#include <stdlib.h>
#include <string>

const bool DEBUG = true;

const std::string IMAGE_PATH = "../images/";
const std::string FONT_PATH = "../fonts/";

enum class GameState { PAUSE, IN_PROGRESS };
enum class UIState {
  IN_GAME,
  IN_ITEMLIST,
  IN_SKILLS,
  IN_STATS,
  IN_SHOP,
  IN_CONVO
};

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;