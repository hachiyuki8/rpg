#pragma once
#include <SDL.h>
#include <map>
#include <string>

const bool DEBUG = true;

const std::string IMAGE_PATH = "../images/";
const std::string FONT_PATH = "../fonts/";

enum class GameState { PAUSE, IN_PROGRESS };
enum class UIState { IN_GAME, IN_ITEMLIST, IN_SKILLS };

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
const SDL_Keycode CONFIRM = SDLK_RETURN;

const SDL_Keycode START_GAME = SDLK_CAPSLOCK;
const SDL_Keycode PAUSE_GAME = SDLK_ESCAPE;

enum class TileState { REACHABLE, UNREACHABLE };
const int TILE_SIZE = 80;

enum class ObjectProperty { CAN_COLLIDE, CAN_PICKUP, CAN_INTERACT, CAN_USE };
const int OBJECT_SIZE = 40;

const int ITEMLIST_WIDTH = 960;
const int ITEMLIST_HEIGHT = 540;
const int ITEMLIST_GRID_SIZE = 60;
const int ITEMLIST_OBJECT_SIZE = 40;
const int ITEM_LIMIT = (ITEMLIST_WIDTH / ITEMLIST_GRID_SIZE) *
                       (ITEMLIST_HEIGHT / ITEMLIST_GRID_SIZE);

const int SKILLS_SCREEN_WIDTH = 960;
const int SKILLS_SCREEN_HEIGHT = 540;
const std::map<int, int> SKILLS_EXP_PER_LEVEL = {{0, 100}, {1, 200}, {2, 400}};
const std::map<std::string, bool> SKILLS_ALL = {{"testing 1", true},
                                                {"testing 2", false}};