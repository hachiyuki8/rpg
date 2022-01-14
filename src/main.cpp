#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "assetManager.h"
#include "init.h"

bool loop();
void kill();

const Uint8 *keys = SDL_GetKeyboardState(NULL);
static GameState gameState = GameState::PAUSE;

/*
 * game
 */
int main(int argc, char **args) {
  // game assets initialization
  if (!AssetManager::init()) {
    system("pause");
    return 1;
  }

  // game content initialization
  init();

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
    renderStartingScreen();
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
              if (AssetManager::player->quit()) {
                gameState = GameState::PAUSE;
              }
            }
            break;
          case HELP:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->showHelp();
            }
            break;
          case SHOW_INVENTORY:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->showInventory();
            }
            break;
          case SHOW_SKILLS:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->showSkills();
            }
            break;
          case SHOW_STATS:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->showStats();
            }
            break;
          case SHOW_LOGS:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->showLogs();
            }
            break;
          case PICKUP_ITEM:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->pickupObject();
            }
            break;
          case INTERACT:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->interact();
            }
            break;
          case CONFIRM:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->confirm();
            }
            break;
          case SDLK_t:
            // testing
            AssetManager::player->testing();
            break;
        }
      case SDL_MOUSEBUTTONDOWN:
        switch (evt.button.button) {
          case SDL_BUTTON_LEFT:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->click(evt.button.x, evt.button.y, true);
            }
            break;
          case SDL_BUTTON_RIGHT:
            if (gameState == GameState::IN_PROGRESS) {
              AssetManager::player->click(evt.button.x, evt.button.y, false);
            }
            break;
        }
    }
  }

  if (gameState == GameState::IN_PROGRESS) {
    AssetManager::player->update(keys);
    AssetManager::player->render(AssetManager::renderer);
  }

  SDL_RenderPresent(AssetManager::renderer);

  Uint64 end = SDL_GetPerformanceCounter();
  float elapsedMS =
      (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
  // cap FPS
  SDL_Delay(floor((1000.0f / FRAME_RATE) - elapsedMS));

  return true;
}

void kill() {
  free();
  AssetManager::quit();
}