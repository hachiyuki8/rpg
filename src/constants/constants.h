#pragma once

const bool DEBUG = true;

const int FRAME_RATE = 60;

enum class Mode { GAME, EDITOR };
enum class GameState { PAUSE, IN_PROGRESS };
enum class UIState {
  IN_GAME,
  IN_HELP,
  IN_INVENTORY,
  IN_SKILLS,
  IN_STATS,
  IN_SHOP,
  IN_CONVO,
};
enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class MovementState { IDLE, WALK, ATTACK, DEATH };

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;