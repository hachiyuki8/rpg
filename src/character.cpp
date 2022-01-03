#include "character.h"

int Character::nextID = 0;

Character::Character(SDL_Texture *t, SDL_Texture *itemlist_t,
                     SDL_Texture *skills_t, bool isCurrent, float x, float y,
                     float w, float h, float xV, float yV) {
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
  isCurPlayer = isCurrent;

  itemlist.texture = itemlist_t;
  skills.texture = skills_t;
  skills.initAllSkills();

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
  switch (uiState) {
  case UIState::IN_GAME:
    itemlist.open();
    uiState = UIState::IN_ITEMLIST;
    break;
  case UIState::IN_ITEMLIST:
    itemlist.close();
    uiState = UIState::IN_GAME;
    break;
  default:
    break;
  }
}

void Character::showSkills() {
  switch (uiState) {
  case UIState::IN_GAME:
    skills.open();
    uiState = UIState::IN_SKILLS;
    break;
  case UIState::IN_SKILLS:
    skills.close();
    uiState = UIState::IN_GAME;
    break;
  default:
    break;
  }
}

void Character::pickupObject() {
  if (uiState != UIState::IN_GAME) {
    return;
  }

  for (auto &o : curMap->objects) {
    if (o.canPickup(xPos, yPos, width, height)) {
      if (DEBUG) {
        std::cout << "Picking up object" << std::endl;
        o.print();
      }
      itemlist.addItem(o);
      curMap->removeObject(o);
      return;
    }
  }
}

void Character::upgradeSkill(std::string s, int exp) {
  skills.upgradeSkill(s, exp);
  if (DEBUG) {
    skills.print();
  }
}

void Character::interact() {
  if (uiState != UIState::IN_GAME) {
    return;
  }

  Map *newMap;
  float newX, newY;
  std::tie(newMap, newX, newY) =
      curMap->onInteract(curMap, xPos, yPos, width, height);
  if (newMap != curMap) {
    // change map, reset position to new tile center
    curMap = newMap;
    xPos = newX - width / 2;
    yPos = newY - height / 2;
  }
}

void Character::click(float x, float y, bool isLeft) {
  switch (uiState) {
  case UIState::IN_ITEMLIST:
    itemlist.onClick(x, y, isLeft);
    break;
  default:
    break;
  }
}

void Character::confirm() {
  switch (uiState) {
  case UIState::IN_ITEMLIST:
    itemlist.onConfirm();
    break;
  default:
    break;
  }
}

void Character::update(const Uint8 *keys) {
  if (uiState != UIState::IN_GAME) {
    return;
  }

  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  move(keys, dT);

  lastUpdate = current;
}

void Character::render(SDL_Renderer *renderer) {
  curMap->render(renderer);

  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);

  itemlist.render(renderer);
}

void Character::move(const Uint8 *keys, float dT) {
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