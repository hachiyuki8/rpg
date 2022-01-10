#pragma once
#include "constants.h"

const int CONVO_SCREEN_WIDTH = 1280;
const int CONVO_SCREEN_HEIGHT = 240;
const int CONVO_BORDER = 60;
const int CONVO_ICON_SIZE = (CONVO_SCREEN_HEIGHT - CONVO_BORDER * 2);
const int CONVO_OFFSET_LEFT = CONVO_ICON_SIZE * 1.5;
const int CONVO_LINE_HEIGHT = (CONVO_SCREEN_HEIGHT - CONVO_BORDER * 2) / 3;

const int CONVO_TEXTURE = 6;
const int CONVO_FONT = 1;
const SDL_Color CONVO_COLOR = {0, 0, 0};