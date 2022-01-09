#include "globals.h"
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

/*
 * game
 */
int main(int argc, char **args) {
  if (!init()) {
    system("pause");
    return 1;
  }

  // player initialization
  Character player(80, 180);
  player.init();
  curPlayer = &player;
  curPlayer->curMap = &maps[0];

  while (loop()) {
  }

  // end the program
  kill();
  return 0;
}

bool loop() {
  SDL_Event evt;

  // clear the screen to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

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
      case PAUSE_GAME:
        if (gameState == GameState::IN_PROGRESS) {
          gameState = GameState::PAUSE;
        }
        break;
      case HELP:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showHelp();
        }
        break;
      case SHOW_ITEMS:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showItemlist();
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

  SDL_RenderPresent(renderer);
  return true;
}

void updatePlayer(const Uint8 *keys) { curPlayer->update(keys); }

void renderPlayer() { curPlayer->render(renderer); }

void renderStartScreen() {
  startup_t = SDL_CreateTextureFromSurface(renderer, startup_text);
  SDL_Rect dest = {(SCREEN_WIDTH - startup_text->w) / 2,
                   (SCREEN_HEIGHT - startup_text->h) / 2, startup_text->w,
                   startup_text->h};
  SDL_RenderCopy(renderer, startup_t, NULL, &dest);
}

void kill() {
  for (auto &f : fonts) {
    TTF_CloseFont(f);
  }

  SDL_FreeSurface(startup_text);
  SDL_DestroyTexture(startup_t);
  SDL_DestroyTexture(player_t);

  for (auto &t : npcTextures) {
    SDL_DestroyTexture(t);
  }
  for (auto &t : tileTextures) {
    SDL_DestroyTexture(t);
  }
  for (auto &t : objectTextures) {
    SDL_DestroyTexture(t);
  }
  for (auto &t : uiTextures) {
    SDL_DestroyTexture(t);
  }
  for (auto &t : keyTextures) {
    SDL_DestroyTexture(t.second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}