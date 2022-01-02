#include "character.h"

int Character::nextID = 0;

Character::Character(SDL_Texture *t, SDL_Texture *itemlist_t, bool flag,
                     float x, float y, float w, float h, float xV, float yV) {
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
  isCurPlayer = flag;
  itemlist.texture = itemlist_t;

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

void Character::showItemlist() {
  if (!isActive && !itemlist.isShowing) {
    return;
  }
  itemlist.isShowing = !itemlist.isShowing;
  isActive = !isActive;
}

void Character::pickupObject(Map *map) {
  if (!isActive) {
    return;
  }
  for (auto &o : map->objects) {
    if (o.canPickup(xPos, yPos, width, height)) {
      if (DEBUG) {
        std::cout << "Picking up object" << std::endl;
        o.print();
      }
      itemlist.addItem(o);
      map->removeObject(o);
      return;
    }
  }
}

void Character::interact(Map *map) {
  if (!isActive) {
    return;
  }
  map->onInteract(xPos, yPos, width, height);
}

void Character::click(float x, float y, bool isLeft) {
  if (itemlist.isShowing) {
    itemlist.onClick(x, y, isLeft);
  }
  // TO-DO: handle other cases such as skill screen
}

void Character::update(const Uint8 *keys, Map *curMap) {
  if (!isActive) {
    return;
  }
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  move(keys, dT, curMap);

  lastUpdate = current;
}

void Character::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);

  itemlist.render(renderer);
}

void Character::move(const Uint8 *keys, float dT, Map *curMap) {
  // TO-DO: check collision
  if (keys[CONTROL_UP] && yPos - yVel * dT >= 0 &&
      !curMap->isInvalidPosition(xPos, yPos - yVel * dT, width, height)) {
    yPos -= yVel * dT;
  }
  if (keys[CONTROL_DOWN] && yPos + yVel * dT + height <= SCREEN_HEIGHT &&
      !curMap->isInvalidPosition(xPos, yPos + yVel * dT, width, height)) {
    yPos += yVel * dT;
  }
  if (keys[CONTROL_LEFT] && xPos - xVel * dT >= 0 &&
      !curMap->isInvalidPosition(xPos - xVel * dT, yPos, width, height)) {
    xPos -= xVel * dT;
  }
  if (keys[CONTROL_RIGHT] && xPos + xVel * dT + width <= SCREEN_WIDTH &&
      !curMap->isInvalidPosition(xPos + xVel * dT, yPos, width, height)) {
    xPos += xVel * dT;
  }
}