#include "character.h"

int Character::nextID = 0;

Character::Character(SDL_Texture *t, float x, float y, float w, float h,
                     float xV, float yV) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating character " << ID << std::endl;
  }

  texture = t;
  xPos = x;
  yPos = y;
  width = w;
  height = h;
  xVel = xV;
  yVel = yV;

  lastUpdate = SDL_GetTicks();
}

Character::~Character() {
  if (DEBUG) {
    std::cout << "Destroying character " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
}

void Character::print() {
  std::cout << "Character " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

void Character::update(const Uint8 *keys) {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  move(keys, dT);

  lastUpdate = current;
}

void Character::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}

void Character::move(const Uint8 *keys, float dT) {
  // TO-DO: check collision
  if (keys[CONTROL_UP] && yPos - yVel * dT >= 0) {
    yPos -= yVel * dT;
  }
  if (keys[CONTROL_DOWN] && yPos + yVel * dT + height <= SCREEN_HEIGHT) {
    yPos += yVel * dT;
  }
  if (keys[CONTROL_LEFT] && xPos - xVel * dT >= 0) {
    xPos -= xVel * dT;
  }
  if (keys[CONTROL_RIGHT] && xPos + xVel * dT + width <= SCREEN_WIDTH) {
    xPos += xVel * dT;
  }
}