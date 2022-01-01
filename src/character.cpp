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
  itemlist_texture = itemlist_t;
  xPos = x;
  yPos = y;
  width = w;
  height = h;
  xVel = xV;
  yVel = yV;
  isCurPlayer = flag;
  isShowingObjects = false;

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

void Character::addObject(Object o) { objects.push_back(o); }

void Character::removeObject(Object o) {
  objects.erase(std::remove(objects.begin(), objects.end(), o), objects.end());
}

void Character::showObjects() {
  isShowingObjects = !isShowingObjects;
  std::cout << "Number of items: " << objects.size() << std::endl;
}

void Character::pickupObject(Map *map) {
  for (auto &o : map->objects) {
    if (o.canPickup(xPos, yPos, width, height)) {
      if (DEBUG) {
        std::cout << "Picking up object" << std::endl;
        o.print();
      }
      addObject(o);
      map->removeObject(o);
      return;
    }
  }
}

void Character::interact(Map *map) {
  map->onInteract(xPos, yPos, width, height);
}

void Character::update(const Uint8 *keys, Map *curMap) {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  move(keys, dT, curMap);

  lastUpdate = current;
}

void Character::renderObjectList(SDL_Renderer *renderer) {
  float nextX = (SCREEN_WIDTH - ITEMLIST_WIDTH) / 2;
  float nextY = (SCREEN_HEIGHT - ITEMLIST_HEIGHT) / 2;
  int nextRow = 0;
  int nextCol = 0;

  for (int row = 0; row < ITEMLIST_HEIGHT / ITEMLIST_GRID_SIZE; row++) {
    for (int col = 0; col < ITEMLIST_WIDTH / ITEMLIST_GRID_SIZE; col++) {
      SDL_Rect r;
      r.x = nextX + col * ITEMLIST_GRID_SIZE;
      r.y = nextY + row * ITEMLIST_GRID_SIZE;
      r.w = ITEMLIST_GRID_SIZE;
      r.h = ITEMLIST_GRID_SIZE;
      SDL_RenderCopy(renderer, itemlist_texture, NULL, &r);
    }
  }

  int offset = (ITEMLIST_GRID_SIZE - ITEMLIST_OBJECT_SIZE) / 2;
  for (auto &o : objects) {
    o.render(renderer, nextX + offset, nextY + offset, ITEMLIST_OBJECT_SIZE,
             ITEMLIST_OBJECT_SIZE);

    if (nextCol + 1 < ITEMLIST_WIDTH / ITEMLIST_GRID_SIZE) {
      nextCol++;
      nextX += ITEMLIST_GRID_SIZE;
    } else if (nextRow + 1 < ITEMLIST_HEIGHT / ITEMLIST_GRID_SIZE) {
      nextCol = 0;
      nextX = (SCREEN_WIDTH - ITEMLIST_WIDTH) / 2;
      nextRow++;
      nextY += ITEMLIST_GRID_SIZE;
    } else {
      // TO-DO: display a new page
    }
  }
}

void Character::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);

  if (isShowingObjects) {
    renderObjectList(renderer);
  }
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