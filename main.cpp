#include "character.h"
#include "constants.h"
#include "map.h"
#include "object.h"
#include "tile.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *main_font;

SDL_Texture *startup_t;
SDL_Surface *startup_text;

std::vector<SDL_Texture *> characterTextures;
std::vector<SDL_Texture *> tileTextures;
std::vector<SDL_Texture *> objectTextures;

Map *curMap;
std::vector<Character> characters;
std::vector<Object> objects;

const Uint8 *keys = SDL_GetKeyboardState(NULL);
static GameState gameState = GameState::PAUSE;

bool init();
bool loop();
void kill();

void updateCharacters(const Uint8 *key, Map *curMap);
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

  Character player(characterTextures[0]);
  characters.push_back(std::move(player));

  Map map(tileTextures);
  Object coin(objectTextures[0], 100, 100);
  coin.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  coin.addObjectProperty(ObjectProperty::CAN_PICKUP);
  map.addObject(coin);
  Object coin2(objectTextures[0], 300, 300);
  map.addObject(coin2);
  curMap = &map;

  while (loop()) {
  }

  // End the program
  kill();
  return 0;
}

bool loop() {
  SDL_Event evt;

  // clear the screen to white
  SDL_SetRenderDrawColor(renderer, 250, 255, 255, 255);
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
      case SDLK_RETURN:
        gameState = GameState::IN_PROGRESS;
        break;
      case SDLK_ESCAPE:
        gameState = GameState::PAUSE;
        break;
      case SHOW_ITEMS:
        // TO-DO: add UI
        characters[0].showObjects();
        break;
      case PICKUP_ITEM:
        characters[0].pickupObject(curMap);
        break;
      }
    }
  }

  if (gameState == GameState::IN_PROGRESS) {
    curMap->render(renderer);

    updateCharacters(keys, curMap);
    renderCharacters();
  }

  SDL_RenderPresent(renderer);
  return true;
}

void updateCharacters(const Uint8 *keys, Map *curMap) {
  for (auto &c : characters) {
    c.update(keys, curMap);
  }
}

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
  main_font = TTF_OpenFont("fonts/main.ttf", 36);
  if (!main_font) {
    std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    return false;
  }

  SDL_Color text_color = {0, 0, 0};
  startup_text = TTF_RenderText_Solid(
      main_font, "Press RETURN to start/resume the game", text_color);
  if (!startup_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }

  SDL_Surface *image = SDL_LoadBMP("images/character.bmp");
  if (!image) {
    std::cout << "Error loading image character.bmp: " << SDL_GetError()
              << std::endl;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }
  characterTextures.push_back(texture);

  image = SDL_LoadBMP("images/tile.bmp");
  if (!image) {
    std::cout << "Error loading image tile.bmp: " << SDL_GetError()
              << std::endl;
  }
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }
  tileTextures.push_back(texture);

  image = SDL_LoadBMP("images/tile2.bmp");
  if (!image) {
    std::cout << "Error loading image tile2.bmp: " << SDL_GetError()
              << std::endl;
  }
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }
  tileTextures.push_back(texture);

  image = SDL_LoadBMP("images/object.bmp");
  if (!image) {
    std::cout << "Error loading image object.bmp: " << SDL_GetError()
              << std::endl;
  }
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }
  objectTextures.push_back(texture);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  return true;
}

void kill() {
  TTF_CloseFont(main_font);
  SDL_FreeSurface(startup_text);
  SDL_DestroyTexture(startup_t);
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