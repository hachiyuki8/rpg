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
const SDL_Keycode PICKUP_ITEM = SDLK_e;
const SDL_Keycode INTERACT = SDLK_f;

enum class TileState { REACHABLE, INTERACTABLE, UNREACHABLE };
const int TILE_SIZE = 80;

enum class ObjectProperty { CAN_COLLIDE, CAN_PICKUP, CAN_INTERACT, CAN_USE };
const int OBJECT_SIZE = 40;

const int ITEMLIST_WIDTH = 960;
const int ITEMLIST_HEIGHT = 540;
const int ITEMLIST_GRID_SIZE = 60;
const int ITEMLIST_OBJECT_SIZE = 40;
const int ITEM_LIMIT = (ITEMLIST_WIDTH / ITEMLIST_GRID_SIZE) *
                       (ITEMLIST_HEIGHT / ITEMLIST_GRID_SIZE);