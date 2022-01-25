#include "mapEditor.h"

MapEditor::MapEditor() {}

MapEditor::~MapEditor() {}

bool MapEditor::init() {
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

  window = SDL_CreateWindow("Map Editor", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, MAP_EDITOR_SCREEN_WIDTH,
                            MAP_EDITOR_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

  if (!initTextures_EditorUI()) {
    std::cout << "[Map Editor] Editor UI texture initialization failed"
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

  initObjects(false);  // initialize objects in editor mode
  for (auto &kv : MapEditor::allObjectsIndex) {
    std::cout << kv.first << ": " << kv.second << std::endl;
  }

  return true;
}

void MapEditor::quit() {
  for (auto &kv : editorTextures) {
    SDL_DestroyTexture(kv.second);
  }
  for (auto &kv : objectTextures) {
    SDL_DestroyTexture(kv.second);
  }
  for (auto &kv : tileTextures) {
    SDL_DestroyTexture(kv.second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void MapEditor::render() { itemlist.render(renderer); }

bool MapEditor::initTextures_EditorUI() {
  for (auto &s : EDITOR_UIS) {
    std::string path = EDITOR_UI_PATH + s;
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
    editorTextures[s] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

bool MapEditor::initTextures_Object() {
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

bool MapEditor::initTextures_Tile() {
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