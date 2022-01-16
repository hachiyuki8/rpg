#include "character.h"

int Character::nextID = 0;

Character::Character(float x, float y, float w, float h, float xV, float yV) {
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

void Character::print() {
  std::cout << "Character " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
  std::cout << "-cam: (" << camX << ", " << camY << ")" << std::endl;
}

void Character::init() {
  stats.initAllStats();
  skills.initAllSkills();
  help.init();
  logs.addLog("-Press H to see help/controls");
}

bool Character::quit() {
  switch (uiState) {
    case UIState::IN_GAME:
      return true;
    case UIState::IN_SHOP:
    case UIState::IN_CONVO:
      curNPC->onQuit();
      curNPC = NULL;
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
      movementState = MovementState::IDLE;
      break;
    case UIState::IN_HELP:
      help.close();
      uiState = UIState::IN_GAME;
      break;
    default:
      break;
  }
}

void Character::showInventory() {
  switch (uiState) {
    case UIState::IN_GAME:
      inventory.open(&logs);
      uiState = UIState::IN_INVENTORY;
      movementState = MovementState::IDLE;
      break;
    case UIState::IN_INVENTORY:
      inventory.close();
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
      movementState = MovementState::IDLE;
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
      movementState = MovementState::IDLE;
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

  for (auto &ow : curMap->objectWrappers) {
    if (ow.canPickup(xPos, yPos, width, height)) {
      if (ow.object->type == ObjectType::MONEY) {
        stats.increaseMoney(&logs, ow.object->value);
        curMap->removeObject(ow);
      } else {
        bool success = inventory.addItem(&logs, ow.object, 1);
        if (success) {
          std::string s = "-Picked up " + ow.object->name;
          logs.addLog(s);
          curMap->removeObject(ow);
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
      curMap->onInteract(this, xPos, yPos, width, height);
  movementState = MovementState::IDLE;
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
    case UIState::IN_INVENTORY:
      m = inventory.onClick(&logs, x, y, isLeft);  // m > 0 if selling items
      stats.increaseMoney(&logs, m);
      break;
    case UIState::IN_SKILLS:
      skills.onClick(x, y, isLeft);
      break;
    case UIState::IN_SHOP:
      curNPC->onClick(x, y);
      break;
    case UIState::IN_GAME:
      attack();
      break;
    default:
      break;
  }
}

void Character::confirm() {
  switch (uiState) {
    case UIState::IN_INVENTORY:
      inventory.onConfirm(&logs);
      break;
    case UIState::IN_SHOP:
      curNPC->onConfirm(this);
      break;
    case UIState::IN_CONVO:
      if (!curNPC->onConfirm(this)) {
        curNPC = NULL;
        uiState = UIState::IN_GAME;
      }
      break;
    default:
      break;
  }
}

bool Character::isInvalidPosition(float x, float y, float w, float h) {
  return (xPos < x + w && x < xPos + width && yPos < y + h &&
          y < yPos + height);
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
  // map
  curMap->render(renderer, camX, camY, camW, camH);

  // animation
  SDL_Rect r;
  r.x = xPos - camX;
  r.y = yPos - camY;
  r.w = width;
  r.h = height;
  playerIndices[movementState][direction].second++;
  if (playerIndices[movementState][direction].second >
      CHARACTER_PER_FRAME_LENGTH) {
    // switch to next frame
    playerIndices[movementState][direction].second = 0;
    playerIndices[movementState][direction].first += 1;
    playerIndices[movementState][direction].first %=
        playerTextures[movementState][direction].size();

    // update movement state after attack animation finished
    if (movementState == MovementState::ATTACK &&
        playerIndices[movementState][direction].first == 0) {
      movementState = MovementState::IDLE;
    }
  }
  SDL_RenderCopy(renderer,
                 playerTextures[movementState][direction]
                               [playerIndices[movementState][direction].first],
                 NULL, &r);

  // screens
  help.render(renderer);
  inventory.render(renderer);
  skills.render(renderer);
  stats.render(renderer);
  if (curNPC) {
    curNPC->renderScreen(renderer);
  }

  if (uiState != UIState::IN_CONVO) {
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
    movementState = MovementState::IDLE;
  } else {
    movementState = MovementState::WALK;
  }
}

void Character::upgradeSkill(std::string s, int exp) {
  skills.upgradeSkill(&logs, s, exp);
}

void Character::increaseExp(int exp) { stats.increaseExp(&logs, exp); }

void Character::increaseStat(std::string s, int val) {
  stats.increaseAttribute(&logs, s, val);
}

void Character::increaseMoney(int m) { stats.increaseMoney(&logs, m); }

void Character::attack() {
  if (movementState == MovementState::ATTACK) {
    return;  // don't register if still in last attack animation
  }

  std::tuple<int, Enemy *> res =
      curMap->onAttack(stats.getAttribute("attack"), xPos, yPos, width, height);
  int diff = std::get<0>(res);
  Enemy *enemy = std::get<1>(res);
  if (enemy) {
    // enemy killed, add reward
    calculateStatsReward(enemy, diff);
    for (auto &r : enemy->rewards) {
      std::string s =
          "-Got " + std::to_string(std::get<1>(r)) + " " + std::get<0>(r)->name;
      logs.addLog(s);
      // add items one at a time to max out quantity until item limit reached
      for (int i = 0; i < std::get<1>(r); i++) {
        inventory.addItem(&logs, std::get<0>(r), 1);
      }
    }
  } else if (diff >= 0) {
    // only take damage if enemy is still alive
    movementState = MovementState::ATTACK;
    int dmg = calculateDamage(diff);
    std::cout << "Dmg: " << dmg << std::endl;
    stats.changeHP(dmg * -1);
    // TODO: if HP<0 do something?
  }
}

int Character::calculateDamage(int diff) {
  return diff * 10;  // TODO: also not sure
}

void Character::calculateStatsReward(Enemy *e, int diff) {
  e->print();
  // TODO: calculate EXP and money reward based on difficulty
}

void Character::testing() { print(); }