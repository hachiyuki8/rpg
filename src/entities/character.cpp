#include "character.h"
#include "../screens/shop.h"

int Character::nextID = 0;

Character::Character(float x, float y, float w, float h, float xV, float yV) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating character " << ID << std::endl;
  }

  stillTextures = playerStillTextures;
  walkTextures = playerWalkTextures;
  xPos = x;
  yPos = y;
  width = w;
  height = h;
  xVel = xV;
  yVel = yV;

  camX = xPos + w / 2 - SCREEN_WIDTH / 2;
  camY = yPos + h / 2 - SCREEN_HEIGHT / 2;
  // for now assume camW and camH never change
  camW = SCREEN_WIDTH;
  camH = SCREEN_HEIGHT;

  lastUpdate = SDL_GetTicks();
}

Character::~Character() {
  if (DEBUG) {
    std::cout << "Destroying character " << ID << std::endl;
  }
}

void Character::init() {
  stats.initAllStats();
  skills.initAllSkills();
  help.init();
  logs.addLog("-Press H to see help/controls");
}

void Character::print() {
  std::cout << "Character " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
  std::cout << "-cam: (" << camX << ", " << camY << ")" << std::endl;
}

bool Character::quit() {
  switch (uiState) {
  case UIState::IN_GAME:
    return true;
  case UIState::IN_SHOP:
    curShop->close();
    curShop = NULL;
    uiState = UIState::IN_GAME;
    return false;
  case UIState::IN_CONVO:
    curConvoNPC->quitConvo();
    curConvoNPC = NULL;
    uiState = UIState::IN_GAME;
    return false;
  default:
    return false;
  }
}

void Character::showHelp() {
  switch (uiState) {
  case UIState::IN_GAME:
    help.open();
    uiState = UIState::IN_HELP;
    movementState = MovementState::STILL;
    break;
  case UIState::IN_HELP:
    help.close();
    uiState = UIState::IN_GAME;
    break;
  default:
    break;
  }
}

void Character::showItemlist() {
  switch (uiState) {
  case UIState::IN_GAME:
    itemlist.open(&logs);
    uiState = UIState::IN_ITEMLIST;
    movementState = MovementState::STILL;
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
    movementState = MovementState::STILL;
    break;
  case UIState::IN_SKILLS:
    skills.close();
    uiState = UIState::IN_GAME;
    break;
  default:
    break;
  }
}

void Character::showStats() {
  switch (uiState) {
  case UIState::IN_GAME:
    stats.open();
    uiState = UIState::IN_STATS;
    movementState = MovementState::STILL;
    break;
  case UIState::IN_STATS:
    stats.close();
    uiState = UIState::IN_GAME;
    break;
  default:
    break;
  }
}

void Character::showLogs() { logs.toggleShow(); }

void Character::pickupObject() {
  if (uiState != UIState::IN_GAME) {
    return;
  }

  for (auto &o : curMap->objects) {
    if (o.canPickup(xPos, yPos, width, height)) {
      if (o.type == ObjectType::MONEY) {
        stats.increaseMoney(&logs, o.value);
        curMap->removeObject(o);
      } else {
        bool success = itemlist.addItem(&logs, o, 1);
        if (success) {
          std::string s = "-Picked up " + o.name;
          logs.addLog(s);
          curMap->removeObject(o);
        }
      }
      return;
    }
  }
}

void Character::interact() {
  if (uiState != UIState::IN_GAME) {
    return;
  }

  Map *newMap;
  float newX, newY;
  std::tie(newMap, newX, newY) =
      curMap->onInteract(this, curMap, xPos, yPos, width, height);
  movementState = MovementState::STILL;
  if (newMap != curMap) {
    // change map, reset position to new tile center
    curMap = newMap;
    xPos = newX - width / 2;
    yPos = newY - height / 2;
  }
}

void Character::click(float x, float y, bool isLeft) {
  int m;
  switch (uiState) {
  case UIState::IN_ITEMLIST:
    m = itemlist.onClick(&logs, x, y, isLeft); // m > 0 if selling items
    stats.increaseMoney(&logs, m);
    break;
  case UIState::IN_SKILLS:
    skills.onClick(x, y, isLeft);
    break;
  case UIState::IN_SHOP:
    curShop->onClick(x, y);
    break;
  // case UIState::IN_GAME:
  //   attack();
  default:
    break;
  }
}

void Character::confirm() {
  switch (uiState) {
  case UIState::IN_ITEMLIST:
    itemlist.onConfirm(&logs);
    break;
  case UIState::IN_SKILLS:
    skills.onConfirm();
    break;
  case UIState::IN_SHOP:
    curShop->onConfirm(this);
    break;
  case UIState::IN_CONVO:
    if (!curConvoNPC->nextConvo()) {
      curConvoNPC = NULL;
      uiState = UIState::IN_GAME;
    }
    break;
  default:
    break;
  }
}

void Character::update(const Uint8 *keys) {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  if (uiState == UIState::IN_GAME) {
    move(keys, dT);
  }

  lastUpdate = current;
}

void Character::render(SDL_Renderer *renderer) {
  curMap->render(renderer, camX, camY, camW, camH);

  SDL_Rect r;
  r.x = xPos - camX;
  r.y = yPos - camY;
  r.w = width;
  r.h = height;

  switch (movementState) {
  case MovementState::STILL:
    SDL_RenderCopy(renderer, stillTextures[direction], NULL, &r);
    break;
  case MovementState::WALK:
    walkIndices[direction].second++;
    if (walkIndices[direction].second > PER_FRAME_LENGTH) {
      // switch to next frame
      walkIndices[direction].second = 0;
      walkIndices[direction].first =
          (walkIndices[direction].first + 1) % (walkTextures[direction].size());
    }
    SDL_RenderCopy(renderer,
                   walkTextures[direction][walkIndices[direction].first], NULL,
                   &r);
    break;
  default:
    break;
  }

  help.render(renderer);
  itemlist.render(renderer);
  skills.render(renderer);
  stats.render(renderer);
  if (curShop) {
    curShop->render(renderer);
  }

  if (curConvoNPC) {
    curConvoNPC->convo.render(renderer);
  } else {
    logs.render(renderer);
  }
}

void Character::move(const Uint8 *keys, float dT) {
  // update player position
  if (keys[CONTROL_UP] &&
      !curMap->isInvalidPosition(xPos, yPos - yVel * dT, width, height)) {
    yPos -= yVel * dT;
  }
  if (keys[CONTROL_DOWN] &&
      !curMap->isInvalidPosition(xPos, yPos + yVel * dT, width, height)) {
    yPos += yVel * dT;
  }
  if (keys[CONTROL_LEFT] &&
      !curMap->isInvalidPosition(xPos - xVel * dT, yPos, width, height)) {
    xPos -= xVel * dT;
  }
  if (keys[CONTROL_RIGHT] &&
      !curMap->isInvalidPosition(xPos + xVel * dT, yPos, width, height)) {
    xPos += xVel * dT;
  }
  xPos = round(xPos);
  yPos = round(yPos);

  // update camera position
  camX = xPos + width / 2 - SCREEN_WIDTH / 2;
  camY = yPos + height / 2 - SCREEN_HEIGHT / 2;
  if (camX < 0) {
    camX = 0;
  }
  if (camY < 0) {
    camY = 0;
  }
  if (camX + camW > curMap->width) {
    camX = curMap->width - camW;
  }
  if (camY + camH > curMap->height) {
    camY = curMap->height - camH;
  }

  // update movement state and direction
  if (keys[CONTROL_DOWN]) {
    direction = Direction::DOWN;
  }
  if (keys[CONTROL_UP]) {
    direction = Direction::UP;
  }
  if (keys[CONTROL_LEFT]) {
    direction = Direction::LEFT;
  }
  if (keys[CONTROL_RIGHT]) {
    direction = Direction::RIGHT;
  }
  if (!keys[CONTROL_UP] && !keys[CONTROL_DOWN] && !keys[CONTROL_LEFT] &&
      !keys[CONTROL_RIGHT]) {
    movementState = MovementState::STILL;
  } else {
    movementState = MovementState::WALK;
  }
}

void Character::upgradeSkill(std::string s, int exp) {
  skills.upgradeSkill(&logs, s, exp);
}

void Character::increaseExp(int exp) { stats.increaseExp(&logs, exp); }

void Character::increaseStat(std::string s, int val) {
  stats.increaseStat(&logs, s, val);
}

void Character::increaseMoney(int m) { stats.increaseMoney(&logs, m); }

void Character::attack() {
  std::tuple<int, Enemy *> res =
      curMap->onAttack(stats.getStat("attack"), xPos, yPos, width, height);
  if (std::get<0>(res) >= 0) {
    int dmg = calculateDamage(std::get<0>(res));
    stats.increaseHP(dmg * -1);
    // TO-DO: if HP<0 do something?
  }
  if (std::get<1>(res)) {
    // enemy killed, add reward
    calculateReward(std::get<1>(res), std::get<0>(res));
  }
}

int Character::calculateDamage(int diff) {
  return diff * 10; // TO-DO: also not sure
}

void Character::calculateReward(Enemy *e, int diff) {
  e->print(); // TO-DO: add reward
}

void Character::testing() { print(); }