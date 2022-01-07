#include "init.h"

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *main_font, *second_font;

SDL_Texture *startup_t, *player_t;
SDL_Texture *itemlist_t, *skills_t, *stats_t, *logs_t, *shop_t;
SDL_Surface *startup_text;

std::vector<SDL_Texture *> npcTextures;
std::vector<SDL_Texture *> tileTextures;
std::vector<SDL_Texture *> objectTextures;
std::vector<SDL_Texture *> uiTextures;
std::vector<Map> maps;
std::vector<CharacterNPC> NPCs;

bool init() {
  std::string path;

  // libraries
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return false;
  }
  if (TTF_Init() < 0) {
    std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
    return false;
  }
  if (IMG_Init(IMG_INIT_PNG) < 0) {
    std::cout << "Failed to initialize SDL_image: " << IMG_GetError()
              << std::endl;
    return false;
  }

  // basics
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

  // fonts
  path = FONT_PATH + std::string("main.ttf");
  main_font = TTF_OpenFont(path.c_str(), 36);
  if (!main_font) {
    std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    return false;
  }
  second_font = TTF_OpenFont(path.c_str(), 18);
  if (!second_font) {
    std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    return false;
  }

  // texts
  SDL_Color text_color = {0, 0, 0};
  std::string s = "Press " + std::string(SDL_GetKeyName(START_GAME)) +
                  " to start/resume the game";
  startup_text = TTF_RenderText_Solid(main_font, s.c_str(), text_color);
  if (!startup_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }

  // player textures
  path = IMAGE_PATH + std::string("player/player.png");
  SDL_Surface *image = IMG_Load(path.c_str());
  if (!image) {
    std::cout << "Error loading image " << path << ": " << SDL_GetError()
              << std::endl;
  }
  player_t = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!player_t) {
    std::cout << "Error creating texture for" << path << ": " << SDL_GetError()
              << std::endl;
  }

  init_NPC_texture();
  init_object_texture();
  init_tile_texture();
  init_UI_texture();

  // maps
  init_maps();

  // NPCs
  init_NPCs();

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  return true;
}

void init_NPC_texture() {
  for (auto &s : NPCS) {
    std::string path = NPC_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
    }
    npcTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
}

void init_object_texture() {
  for (auto &s : OBJECTS) {
    std::string path = OBJECT_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
    }
    objectTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
}

void init_tile_texture() {
  for (auto &s : TILES) {
    std::string path = TILE_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
    }
    tileTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
}

void init_UI_texture() {
  for (auto &s : UI) {
    std::string path = UI_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
    }
    uiTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
  itemlist_t = uiTextures[3];
  skills_t = uiTextures[4];
  stats_t = uiTextures[12];
  logs_t = uiTextures[13];
  shop_t = uiTextures[6];
}

void init_maps() {
  for (auto &map : MAPS) {
    Map newMap(map);
    maps.push_back(newMap);
  }
}

void init_NPCs() {
  CharacterNPC npc1(npcTextures[0], shop_t, second_font, PlayerState::SHOP_NPC,
                    800, 500);
  NPCs.push_back(npc1);
  maps[0].addNPC(&NPCs[0]);
  Object coin3("coin 3", "coin 00", objectTextures[0], 10, ObjectType::OTHERS,
               600, 600);
  NPCs[0].shop.addItem(coin3, 10);
}