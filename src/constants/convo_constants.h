#pragma once
#include "constants.h"

const int CONVO_SCREEN_WIDTH = 1280;
const int CONVO_SCREEN_HEIGHT = 240;
const int CONVO_BORDER = 60;
const int CONVO_ICON_SIZE = (CONVO_SCREEN_HEIGHT - CONVO_BORDER * 2);
const int CONVO_OFFSET_LEFT = CONVO_ICON_SIZE + CONVO_BORDER;
const int CONVO_LINE_HEIGHT = (CONVO_SCREEN_HEIGHT - CONVO_BORDER * 2) / 10;
const int CONVO_WIDTH = CONVO_SCREEN_WIDTH - CONVO_OFFSET_LEFT - CONVO_BORDER;

const std::string CONVO_TEXTURE = "18_chatbox1.png";
const std::string CONVO_FONT = "1_abaddon_light.ttf";
const int CONVO_FONT_SIZE = 27;
const SDL_Color CONVO_COLOR = {0, 0, 0};