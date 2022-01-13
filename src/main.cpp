#include "assetManager.h"
#include "init.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

bool loop();
void kill();

void updatePlayer(const Uint8 *key);
void renderPlayer();
void renderStartScreen();

Character *curPlayer;
const Uint8 *keys = SDL_GetKeyboardState(NULL);
static GameState gameState = GameState::PAUSE;
SDL_Texture *startup_t;

/*
 * game
 */
int main(int argc, char **args) {
  AssetManager assetManager;
  // game assets initialization
  if (!AssetManager::init()) {
    system("pause");
    return 1;
  }

  // game content initialization
  init();

  // player initialization
  curPlayer = new Character(80, 180);
  curPlayer->init();
  curPlayer->curMap = AssetManager::allMaps[1];

  while (loop()) {
  }

  // end the program
  kill();
  return 0;
}

bool loop() {
  Uint64 start = SDL_GetPerformanceCounter();

  SDL_Event evt;

  // clear the screen to white
  SDL_SetRenderDrawColor(AssetManager::renderer, 255, 255, 255, 255);
  SDL_RenderClear(AssetManager::renderer);

  if (gameState == GameState::PAUSE) {
    renderStartScreen();
  }

  // event loop
  while (SDL_PollEvent(&evt) != 0) {
    switch (evt.type) {
    case SDL_QUIT:
      return false;
    case SDL_KEYDOWN:
      switch (evt.key.keysym.sym) {
      case START_GAME:
        if (gameState != GameState::IN_PROGRESS) {
          gameState = GameState::IN_PROGRESS;
          SDL_Delay(10);
        }
        break;
      case QUIT:
        if (gameState == GameState::IN_PROGRESS) {
          if (curPlayer->quit()) {
            gameState = GameState::PAUSE;
          }
        }
        break;
      case HELP:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showHelp();
        }
        break;
      case SHOW_INVENTORY:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showInventory();
        }
        break;
      case SHOW_SKILLS:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showSkills();
        }
        break;
      case SHOW_STATS:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showStats();
        }
        break;
      case SHOW_LOGS:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showLogs();
        }
        break;
      case PICKUP_ITEM:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->pickupObject();
        }
        break;
      case INTERACT:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->interact();
        }
        break;
      case CONFIRM:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->confirm();
        }
        break;
      case SDLK_t:
        // testing
        curPlayer->testing();
        break;
      }
    case SDL_MOUSEBUTTONDOWN:
      switch (evt.button.button) {
      case SDL_BUTTON_LEFT:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->click(evt.button.x, evt.button.y, true);
        }
        break;
      case SDL_BUTTON_RIGHT:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->click(evt.button.x, evt.button.y, false);
        }
        break;
      }
    }
  }

  if (gameState == GameState::IN_PROGRESS) {
    updatePlayer(keys);

    renderPlayer();
  }

  SDL_RenderPresent(AssetManager::renderer);

  Uint64 end = SDL_GetPerformanceCounter();
  float elapsedMS =
      (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
  // Cap FPS
  SDL_Delay(floor((1000.0f / FRAME_RATE) - elapsedMS));

  return true;
}

void updatePlayer(const Uint8 *keys) { curPlayer->update(keys); }

void renderPlayer() { curPlayer->render(AssetManager::renderer); }

void renderStartScreen() {
  startup_t = SDL_CreateTextureFromSurface(AssetManager::renderer,
                                           AssetManager::startup_text);
  SDL_Rect dest = {(SCREEN_WIDTH - AssetManager::startup_text->w) / 2,
                   (SCREEN_HEIGHT - AssetManager::startup_text->h) / 2,
                   AssetManager::startup_text->w,
                   AssetManager::startup_text->h};
  SDL_RenderCopy(AssetManager::renderer, startup_t, NULL, &dest);
}

void kill() {
  delete curPlayer;
  SDL_DestroyTexture(startup_t);

  AssetManager::free();
}