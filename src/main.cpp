#include "character.h"
#include "constants.h"
#include "map.h"
#include "mapfiles.h"
#include "object.h"
#include "tile.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *main_font;

SDL_Texture *startup_t, *player_t, *itemlist_t;
SDL_Surface *startup_text;

std::vector<SDL_Texture *> characterTextures;
std::vector<SDL_Texture *> tileTextures;
std::vector<SDL_Texture *> objectTextures;

Map *curMap;
Character *curPlayer;
std::vector<Character> characters;
std::vector<Object> objects;

const Uint8 *keys = SDL_GetKeyboardState(NULL);
static GameState gameState = GameState::PAUSE;

void init_tiles();
bool init();
bool loop();
void kill();

void updatePlayer(const Uint8 *key, Map *curMap);
void updateCharacters(const Uint8 *key, Map *curMap);
void renderPlayer();
void renderCharacters();
void renderStartScreen();

/*
 * game
 */
int main(int argc, char **args) {
  if (!init()) {
    system("pause");
    return 1;
  }

  Character player(player_t, itemlist_t, true);
  curPlayer = &player;

  Map map(tileTextures, INITIAL_MAP);
  curMap = &map;

  // hardcoded for testing
  for (int i = 0; i < 5; i++) {
    Object coin(objectTextures[0], 100 * (i + 1), 100 * (i + 1));
    coin.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    coin.addObjectProperty(ObjectProperty::CAN_PICKUP);
    coin.addObjectProperty(ObjectProperty::CAN_USE);
    coin.setInteractRange(5, 5, 5, 5);
    map.addObject(coin);
  }
  Object coin2(objectTextures[0], 600, 600);
  map.addObject(coin2);

  while (loop()) {
  }

  // End the program
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
      case SHOW_ITEMS:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->showItemlist();
        }
        break;
      case PICKUP_ITEM:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->pickupObject(curMap);
        }
        break;
      case INTERACT:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->interact(curMap);
        }
        break;
      case CONFIRM:
        if (gameState == GameState::IN_PROGRESS) {
          curPlayer->confirm();
        }
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
    curMap->render(renderer);

    updatePlayer(keys, curMap);
    updateCharacters(keys, curMap);

    renderPlayer();
    renderCharacters();
  }

  SDL_RenderPresent(renderer);
  return true;
}

void updatePlayer(const Uint8 *keys, Map *curMap) {
  curPlayer->update(keys, curMap);
}

void updateCharacters(const Uint8 *keys, Map *curMap) {
  for (auto &c : characters) {
    c.update(keys, curMap);
  }
}

void renderPlayer() { curPlayer->render(renderer); }

void renderCharacters() {
  for (auto &c : characters) {
    c.render(renderer);
  }
}

void renderStartScreen() {
  startup_t = SDL_CreateTextureFromSurface(renderer, startup_text);
  SDL_Rect dest = {(SCREEN_WIDTH - startup_text->w) / 2,
                   (SCREEN_HEIGHT - startup_text->h) / 2, startup_text->w,
                   startup_text->h};
  SDL_RenderCopy(renderer, startup_t, NULL, &dest);
}

bool init() {
  std::string path;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    return false;
  }
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() < 0) {
    std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
    return false;
  }
  path = FONT_PATH + std::string("main.ttf");
  main_font = TTF_OpenFont(path.c_str(), 36);
  if (!main_font) {
    std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    return false;
  }

  SDL_Color text_color = {0, 0, 0};
  startup_text = TTF_RenderText_Solid(
      main_font, "Press CAPSLOCK to start/resume the game", text_color);
  if (!startup_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }

  // characters
  path = IMAGE_PATH + std::string("character.bmp");
  SDL_Surface *image = SDL_LoadBMP(path.c_str());
  if (!image) {
    std::cout << "Error loading image character.bmp: " << SDL_GetError()
              << std::endl;
  }
  player_t = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!player_t) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }

  // tiles
  init_tiles();

  // objects
  path = IMAGE_PATH + std::string("object.bmp");
  image = SDL_LoadBMP(path.c_str());
  if (!image) {
    std::cout << "Error loading image object.bmp: " << SDL_GetError()
              << std::endl;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }
  objectTextures.push_back(texture);

  // others
  path = IMAGE_PATH + std::string("itemlist.bmp");
  image = SDL_LoadBMP(path.c_str());
  if (!image) {
    std::cout << "Error loading image itemlist.bmp: " << SDL_GetError()
              << std::endl;
  }
  itemlist_t = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!itemlist_t) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  return true;
}

void init_tiles() {
  for (auto &f : TILES) {
    std::string file = TILE_PATH + f;
    SDL_Surface *image = SDL_LoadBMP(file.c_str());
    if (!image) {
      std::cout << "Error loading image: " << SDL_GetError() << std::endl;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (!texture) {
      std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    tileTextures.push_back(texture);
  }
}

void kill() {
  TTF_CloseFont(main_font);
  SDL_FreeSurface(startup_text);
  SDL_DestroyTexture(startup_t);
  SDL_DestroyTexture(player_t);
  SDL_DestroyTexture(itemlist_t);
  for (auto &t : characterTextures) {
    SDL_DestroyTexture(t);
  }
  for (auto &t : tileTextures) {
    SDL_DestroyTexture(t);
  }
  for (auto &t : objectTextures) {
    SDL_DestroyTexture(t);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}