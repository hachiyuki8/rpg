#include "tile.h"

int Tile::nextID = 0;

Tile::Tile(SDL_Texture *t, float x, float y, float s, TileState ts) {
  ID = nextID;
  nextID++;

  texture = t;
  xPos = x;
  yPos = y;
  size = s;
  state = ts;
}

Tile::~Tile() {}

void Tile::print() {
  std::cout << "Tile " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

bool Tile::isOnTile(float x, float y, float w, float h) {
  return (xPos < x + w && x < xPos + size && yPos < y + h && y < yPos + size);
}

bool Tile::isInvalidPosition(float x, float y, float w, float h) {
  return (state == TileState::UNREACHABLE && isOnTile(x, y, w, h));
}

void Tile::setTileState(TileState newState) { state = newState; }

bool Tile::isInTile(float x, float y, float w, float h) {
  return (xPos <= x + w / 2 && x + w / 2 <= xPos + size && yPos <= y + h / 2 &&
          y + h / 2 <= yPos + size);
}

void Tile::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = size;
  r.h = size;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}