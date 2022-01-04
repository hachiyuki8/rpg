#pragma once
#include <SDL.h>

const SDL_Scancode CONTROL_UP = SDL_SCANCODE_W;
const SDL_Scancode CONTROL_LEFT = SDL_SCANCODE_A;
const SDL_Scancode CONTROL_DOWN = SDL_SCANCODE_S;
const SDL_Scancode CONTROL_RIGHT = SDL_SCANCODE_D;

const SDL_Keycode SHOW_ITEMS = SDLK_TAB;
const SDL_Keycode SHOW_SKILLS = SDLK_LSHIFT;
const SDL_Keycode SHOW_STATS = SDLK_p;
const SDL_Keycode PICKUP_ITEM = SDLK_e;
const SDL_Keycode INTERACT = SDLK_f;
const SDL_Keycode CONFIRM = SDLK_RETURN;

const SDL_Keycode START_GAME = SDLK_CAPSLOCK;
const SDL_Keycode PAUSE_GAME = SDLK_ESCAPE;