#include "tile.h"

int Tile::nextID = 0;

Tile::Tile(SDL_Texture *t, float x, float y, float s, TileState ts) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    // std::cout << "Creating tile " << ID << std::endl;
  }

  texture = t;
  xPos = x;
  yPos = y;
  size = s;
  state = ts;
}

Tile::~Tile() {
  if (DEBUG) {
    // std::cout << "Destroying tile " << ID << std::endl;
  }
}

void Tile::print() {
  std::cout << "Tile " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

bool Tile::isOnTile(float x, float y, float w, float h) {
  return (xPos <= x + w && x <= xPos + size && yPos <= y + h &&
          y <= yPos + size);
}

bool Tile::isInvalidPosition(float x, float y, float w, float h) {
  return (state == TileState::UNREACHABLE && isOnTile(x, y, w, h));
}

void Tile::setTileState(TileState newState) { state = newState; }

void Tile::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = size;
  r.h = size;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}

bool Tile::isInTile(float x, float y, float w, float h) {
  return (xPos <= x && x + w <= xPos + size && yPos <= y &&
          y + h <= yPos + size);
}