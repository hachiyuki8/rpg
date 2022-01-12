#pragma once
#include "constants.h"

const int ENEMY_WIDTH = 30;
const int ENEMY_HEIGHT = 30;
const int ENEMY_XVELOCITY_BASE = 120;
const int ENEMY_YVELOCITY_BASE = 75;
const int ENEMY_XVELOCITY_RANGE = 100;
const int ENEMY_YVELOCITY_RANGE = 75;
const int ENEMY_HP = 100;
const int ENEMY_DIFFICULTY =
    0; // TO-DO: there will be a system to calculate damage and reward based on
       // difficulty, character level and stats
const int ENEMY_MAX_DIFFICULTY = 5;
const int ENEMY_PER_FRAME_LENGTH = 10;
const int ENEMY_INTERACTION_RANGE = 5;