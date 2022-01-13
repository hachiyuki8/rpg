#include "assetManager.h"

AssetManager::AssetManager() {}

AssetManager::~AssetManager() {}

bool AssetManager::init() {
  if (!initLibraries()) {
    std::cout << "[Asset Manager] Library initialization failed" << std::endl;
    return false;
  }

  if (!initFonts()) {
    std::cout << "[Asset Manager] Font initialization failed" << std::endl;
    return false;
  }

  // TODO: starting screen (temporary)
  SDL_Color text_color = {0, 0, 0};
  std::string s = "Press " + std::string(SDL_GetKeyName(START_GAME)) +
                  " to start/resume the game";
  startup_text = TTF_RenderText_Solid(allFonts["0_abaddon_bold.ttf"][36],
                                      s.c_str(), text_color);
  if (!startup_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    return false;
  }

  if (!initTextures_Player()) {
    std::cout << "[Asset Manager] Player texture initialization failed"
              << std::endl;
    return false;
  }

  if (!initTextures_NPC()) {
    std::cout << "[Asset Manager] NPC texture initialization failed"
              << std::endl;
    return false;
  }

  if (!initTextures_Object()) {
    std::cout << "[Asset Manager] Object texture initialization failed"
              << std::endl;
    return false;
  }

  if (!initTextures_Tile()) {
    std::cout << "[Asset Manager] Tile texture initialization failed"
              << std::endl;
    return false;
  }

  if (!initTextures_UI()) {
    std::cout << "[Asset Manager] UI texture initialization failed"
              << std::endl;
    return false;
  }

  if (!initTextures_Key()) {
    std::cout << "[Asset Manager] Key texture initialization failed"
              << std::endl;
    return false;
  }

  if (!initTextures_Enemy()) {
    std::cout << "[Asset Manager] Enemy texture initialization failed"
              << std::endl;
    return false;
  }

  return true;
}

void AssetManager::free() {
  for (auto &m : allMaps) {
    delete m;
  }
  for (auto &n : allNPCs) {
    delete n;
  }
  for (auto &e : allEnemies) {
    delete e;
  }

  for (auto &kv : allFonts) {
    for (auto &kv2 : kv.second) {
      TTF_CloseFont(kv2.second);
    }
  }

  SDL_FreeSurface(startup_text); // TODO

  SDL_DestroyTexture(playerIcon);
  for (auto &kv : playerTextures) {
    for (auto &kv2 : kv.second) {
      for (auto &t : kv2.second) {
        SDL_DestroyTexture(t);
      }
    }
  }
  for (auto &kv : enemyTextures) {
    for (auto &kv2 : kv.second) {
      for (auto &kv3 : kv2.second) {
        for (auto &t : kv3.second) {
          SDL_DestroyTexture(t);
        }
      }
    }
  }
  for (auto &kv : npcTextures) {
    SDL_DestroyTexture(kv.second);
  }
  for (auto &kv : tileTextures) {
    SDL_DestroyTexture(kv.second);
  }
  for (auto &kv : objectTextures) {
    SDL_DestroyTexture(kv.second);
  }
  for (auto &kv : uiTextures) {
    SDL_DestroyTexture(kv.second);
  }
  for (auto &kv : keyTextures) {
    SDL_DestroyTexture(kv.second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

bool AssetManager::initLibraries() {
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

  return true;
}

bool AssetManager::initFonts() {
  for (auto &s : FONTS) {
    std::string path = FONT_PATH + s;
    for (auto &size : FONT_SIZES) {
      TTF_Font *font = TTF_OpenFont(path.c_str(), size);
      if (!font) {
        std::cout << "Error loading font " << path << ": " << SDL_GetError()
                  << std::endl;
        return false;
      }
      allFonts[s][size] = font;
    }
  }
  return true;
}

bool AssetManager::initTextures_Player() {
  std::string path = PLAYER_PATH + PLAYER_ICON;
  SDL_Surface *image = IMG_Load(path.c_str());
  if (!image) {
    std::cout << "Error loading image " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  playerIcon = SDL_CreateTextureFromSurface(renderer, image);
  if (!playerIcon) {
    std::cout << "Error creating texture for " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  SDL_FreeSurface(image);

  for (auto &mt : PLAYER_TEXTURES) {
    MovementState movement = mt.first;
    for (auto &dt : mt.second) {
      Direction direction = dt.first;
      for (auto &s : dt.second) {
        std::string path = PLAYER_PATH + s;
        SDL_Surface *image = IMG_Load(path.c_str());
        if (!image) {
          std::cout << "Error loading image " << path << ": " << SDL_GetError()
                    << std::endl;
          return false;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
        if (!texture) {
          std::cout << "Error creating texture for " << path << ": "
                    << SDL_GetError() << std::endl;
          return false;
        }
        playerTextures[movement][direction].push_back(texture);
        SDL_FreeSurface(image);
      }
    }
  }

  return true;
}

bool AssetManager::initTextures_NPC() {
  for (auto &s : CHARACTERS) {
    std::string path = NPC_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    npcTextures[s] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

bool AssetManager::initTextures_Object() {
  for (auto &s : OBJECTS) {
    std::string path = OBJECT_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    objectTextures[s] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

bool AssetManager::initTextures_Tile() {
  for (auto &s : TILES) {
    std::string path = TILE_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    tileTextures[s] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

bool AssetManager::initTextures_UI() {
  for (auto &s : UIS) {
    std::string path = UI_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    uiTextures[s] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

bool AssetManager::initTextures_Key() {
  for (auto &s : KEYS) {
    std::string path = KEY_PATH + s.second;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    keyTextures[s.first] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

bool AssetManager::initTextures_Enemy() {
  for (auto &nt : ENEMY_TEXTURES) {
    std::string name = nt.first;
    for (auto &mt : nt.second) {
      MovementState movement = mt.first;
      for (auto &dt : mt.second) {
        Direction direction = dt.first;
        for (auto &s : dt.second) {
          std::string path = ENEMY_PATH + name + s;
          SDL_Surface *image = IMG_Load(path.c_str());
          if (!image) {
            std::cout << "Error loading image " << path << ": "
                      << SDL_GetError() << std::endl;
            return false;
          }
          SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
          if (!texture) {
            std::cout << "Error creating texture for " << path << ": "
                      << SDL_GetError() << std::endl;
            return false;
          }
          enemyTextures[name][movement][direction].push_back(texture);
          SDL_FreeSurface(image);
        }
      }
    }
  }

  return true;
}

SDL_Window *AssetManager::window;
SDL_Renderer *AssetManager::renderer;
SDL_Surface *AssetManager::startup_text;
std::map<std::string, std::map<int, TTF_Font *>> AssetManager::allFonts;
SDL_Texture *AssetManager::playerIcon;
std::map<MovementState, std::map<Direction, std::vector<SDL_Texture *>>>
    AssetManager::playerTextures;
std::map<std::string, std::map<MovementState,
                               std::map<Direction, std::vector<SDL_Texture *>>>>
    AssetManager::enemyTextures;
std::map<std::string, SDL_Texture *> AssetManager::npcTextures;
std::map<std::string, SDL_Texture *> AssetManager::objectTextures;
std::map<std::string, SDL_Texture *> AssetManager::tileTextures;
std::map<std::string, SDL_Texture *> AssetManager::uiTextures;
std::map<SDL_Keycode, SDL_Texture *> AssetManager::keyTextures;
std::vector<Map *> AssetManager::allMaps;
std::vector<CharacterNPC *> AssetManager::allNPCs;
std::vector<Enemy *> AssetManager::allEnemies;