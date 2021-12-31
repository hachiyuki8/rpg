#pragma once
#include <SDL.h>

const bool DEBUG = true;

enum class GameState { PAUSE, IN_PROGRESS };

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int DEFAULT_CHARACTER_WIDTH = 40;
const int DEFAULT_CHARACTER_HEIGHT = 40;
const int DEFAULT_CHARACTER_XVELOCITY = 160;
const int DEFAULT_CHARACTER_YVELOCITY = 90;

enum class Direction { LEFT, RIGHT, UP, DOWN };
const SDL_Scancode CONTROL_UP = SDL_SCANCODE_W;
const SDL_Scancode CONTROL_LEFT = SDL_SCANCODE_A;
const SDL_Scancode CONTROL_DOWN = SDL_SCANCODE_S;
const SDL_Scancode CONTROL_RIGHT = SDL_SCANCODE_D;

const SDL_Keycode SHOW_ITEMS = SDLK_TAB;
const SDL_Keycode PICKUP_ITEM = SDLK_f;

enum class TileState { REACHABLE, UNREACHABLE };
const int TILE_SIZE = 80;

enum class ObjectProperty { CAN_COLLIDE, CAN_PICKUP, CAN_INTERACT };
const int OBJECT_SIZE = 40;