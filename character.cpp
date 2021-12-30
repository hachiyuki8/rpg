#include "character.h"

int character::nextID = 0;

character::character(SDL_Renderer *renderer, float x, float y, float w, float h,
                     float xV, float yV) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating character " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
  xVel = xV;
  yVel = yV;

  SDL_Surface *image =
      SDL_LoadBMP("images/character.bmp"); // TO-DO: make it a param
  if (!image) {
    std::cout << "Error loading image character.bmp: " << SDL_GetError()
              << std::endl;
  }
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (!texture) {
    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
  }

  lastUpdate = SDL_GetTicks();
}

character::~character() {
  if (DEBUG) {
    std::cout << "Destroying character " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
}

void character::print() {
  std::cout << "Character " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

void character::update(const Uint8 *keys) {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  move(keys, dT);

  lastUpdate = current;
}

void character::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}

void character::move(const Uint8 *keys, float dT) {
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