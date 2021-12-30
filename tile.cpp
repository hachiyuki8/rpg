#include "tile.h"

int tile::nextID = 0;

tile::tile(SDL_Renderer *renderer, float x, float y, float s, TileStates ts) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating tile " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  size = s;
  state = ts;

  SDL_Surface *image = SDL_LoadBMP("images/tile.bmp"); // TO-DO: make it a param
  if (!image) {
    std::cout << "Error loading image character.bmp: " << SDL_GetError()
              << std::endl;
  }
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }
}

tile::~tile() {
  if (DEBUG) {
    std::cout << "Destroying tile " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
}

void tile::print() {
  std::cout << "Tile " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
  std::cout << "-state: " << state << std::endl;
}

bool tile::isOnTile(float x, float y, float w, float h) {
  return (xPos <= x + w && x <= xPos + size && yPos <= y + h &&
          y <= yPos + size);
}

bool tile::isInvalidPosition(float x, float y, float w, float h) {
  return (state == UNREACHABLE && isOnTile(x, y, w, h));
}

bool tile::isInTile(float x, float y, float w, float h) {
  return (xPos <= x && x + w <= xPos + size && yPos <= y &&
          y + h <= yPos + size);
}

void tile::setTileState(TileStates newState) {
  if (DEBUG) {
    std::cout << "Tile " << ID << " updated to " << newState << std::endl;
  }
  state = newState;
}

void tile::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = size;
  r.h = size;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}