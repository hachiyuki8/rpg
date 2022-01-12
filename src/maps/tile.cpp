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

void Tile::render(SDL_Renderer *renderer, float camX, float camY, float camW,
                  float camH) {
  if (xPos + size < camX || xPos > camX + camW || yPos + size < camY ||
      yPos > camY + camH) {
    return;
  }

  SDL_Rect s;
  s.x = std::max(0.0f, round(camX - xPos));
  s.y = std::max(0.0f, round(camY - yPos));
  // rescale
  int actualW, actualH;
  SDL_QueryTexture(texture, NULL, NULL, &actualW, &actualH);
  s.x = s.x / size * actualW;
  s.y = s.y / size * actualH;
  s.w = actualW - s.x;
  s.h = actualH - s.y;

  SDL_Rect r;
  r.x = std::max(0.0f, round(xPos - camX));
  r.y = std::max(0.0f, round(yPos - camY));
  r.w = size - std::max(0.0f, round(camX - xPos));
  r.h = size - std::max(0.0f, round(camY - yPos));

  SDL_RenderCopy(renderer, texture, &s, &r);
}