#include "enemy.h"

#include "../maps/map.h"

int Enemy::nextID = 0;

Enemy::Enemy(std::string n, int diff) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating enemy " << ID << std::endl;
  }

  name = n;
  for (auto &mt : AssetManager::enemyTextures[name]) {
    enemyTextures[mt.first] = mt.second;
  };

  difficulty = diff;
}

Enemy::~Enemy() {
  if (DEBUG) {
    std::cout << "Destroying enemy " << ID << std::endl;
  }
}

void Enemy::print() {
  std::cout << "Enemy " << ID << std::endl;
  std::cout << "-difficulty: " << difficulty << std::endl;
}

void Enemy::addReward(Object *o, int q) {
  rewards.push_back(std::make_tuple(o, q));
}

int Enemy::calculateDamage(int attack) {
  return attack * (2 - (difficulty / ENEMY_MAX_DIFFICULTY));  // TODO: not sure
}

// enemy wrapper

int EnemyWrapper::nextID = 0;

EnemyWrapper::EnemyWrapper(Enemy *e, float xMin, float xMax, float yMin,
                           float yMax, MovementState state, int p, float w,
                           float h, int xVBase, int yVBase, int xVRange,
                           int yVRange) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating enemy wrapper" << ID << std::endl;
  }

  enemy = e;

  xPosMin = xMin;
  xPosMax = xMax;
  yPosMin = yMin;
  yPosMax = yMax;

  xPos = xPosMin;
  yPos = yPosMin;
  width = w;
  height = h;

  xVel = xVBase;
  yVel = yVBase;
  xVelBase = xVBase;
  xVelRange = xVRange;
  yVelBase = yVBase;
  yVelRange = yVRange;

  fullHP = p;
  curHP = p;
  movementState = state;

  lastUpdate = SDL_GetTicks();
}

EnemyWrapper::~EnemyWrapper() {
  if (DEBUG) {
    std::cout << "Destroying enemy wrapper " << ID << std::endl;
  }
}

void EnemyWrapper::print() {
  std::cout << "Enemy wrapper" << ID << std::endl;
  std::cout << "-current HP: " << curHP << std::endl;
}

bool EnemyWrapper::operator==(const EnemyWrapper &ew) const {
  return (ID == ew.ID);
}

bool EnemyWrapper::isInvalidPosition(float x, float y, float w, float h) {
  return (movementState != MovementState::DEATH && xPos < x + w &&
          x < xPos + width && yPos < y + h && y < yPos + height);
}

bool EnemyWrapper::isInRange(float x, float y, float w, float h) {
  return (movementState != MovementState::DEATH &&
          xPos - ENEMY_INTERACTION_RANGE <= x + w &&
          x <= xPos + width + ENEMY_INTERACTION_RANGE &&
          yPos - ENEMY_INTERACTION_RANGE <= y + h &&
          y <= yPos + height + ENEMY_INTERACTION_RANGE);
}

std::pair<int, int> EnemyWrapper::onAttack(float x, int attack) {
  if (movementState == MovementState::DEATH ||
      movementState == MovementState::ATTACK) {
    return std::make_pair(-1, -1);
  }

  bool isAlive = true;

  oldMovementState = movementState;
  movementState = MovementState::ATTACK;
  curHP -= enemy->calculateDamage(attack);
  if (curHP <= 0) {
    curHP = 0;
    movementState = MovementState::DEATH;
    isAlive = false;
  }

  std::cout << "HP: " << curHP << std::endl;

  if (x > xPos + width / 2) {
    xDirection = Direction::RIGHT;
  } else {
    xDirection = Direction::LEFT;
  }
  return std::make_pair(enemy->difficulty, isAlive);
}

void EnemyWrapper::render(Map *curMap, SDL_Renderer *renderer, float camX,
                          float camY, float camW, float camH) {
  move(curMap);

  if (xPos + width < camX || xPos > camX + camW || yPos + height < camY ||
      yPos > camY + camH) {
    return;
  }

  if (movementState != MovementState::DEATH ||
      enemyIndices[movementState][xDirection].first <
          enemy->enemyTextures[movementState][xDirection].size() -
              1) {  // death animation loop only rendered once
    SDL_Rect s;
    s.x = std::max(0.0f, round(camX - xPos));
    s.y = std::max(0.0f, round(camY - yPos));
    // rescale
    // TODO: here assuming all textures have the same size
    int actualW, actualH;
    SDL_QueryTexture(
        enemy->enemyTextures[MovementState::IDLE][Direction::LEFT][0], NULL,
        NULL, &actualW, &actualH);
    s.x = s.x / width * actualW;
    s.y = s.y / height * actualH;
    s.w = actualW - s.x;
    s.h = actualH - s.y;

    SDL_Rect r;
    r.x = std::max(0.0f, round(xPos - camX));
    r.y = std::max(0.0f, round(yPos - camY));
    r.w = width - std::max(0.0f, round(camX - xPos));
    r.h = height - std::max(0.0f, round(camY - yPos));

    // TODO: should be a delay before attacked and start of attack animation
    enemyIndices[movementState][xDirection].second++;
    if (enemyIndices[movementState][xDirection].second >
        ENEMY_PER_FRAME_LENGTH) {
      // switch to next frame
      enemyIndices[movementState][xDirection].second = 0;
      enemyIndices[movementState][xDirection].first += 1;
      enemyIndices[movementState][xDirection].first %=
          enemy->enemyTextures[movementState][xDirection].size();

      // update movement state after attack animation finished
      if (movementState == MovementState::ATTACK &&
          enemyIndices[movementState][xDirection].first == 0) {
        movementState = oldMovementState;
      }
    }

    SDL_RenderCopy(
        renderer,
        enemy->enemyTextures[movementState][xDirection]
                            [enemyIndices[movementState][xDirection].first],
        NULL, &r);

    // health bar
    r.x = r.x + width / 2 - ENEMY_HEALTH_BAR_BG_WIDTH / 2;
    r.y = r.y - ENEMY_HEALTH_BAR_BG_HEIGHT;
    r.w = ENEMY_HEALTH_BAR_BG_WIDTH;
    r.h = ENEMY_HEALTH_BAR_BG_HEIGHT;
    SDL_RenderCopy(renderer, enemy->healthbarbg_texture, NULL, &r);
    r.x += ENEMY_HEALTH_BAR_XPOS;
    r.y += ENEMY_HEALTH_BAR_YPOS;
    r.w = ENEMY_HEALTH_BAR_WIDTH * curHP / fullHP;
    r.h = ENEMY_HEALTH_BAR_HEIGHT;
    SDL_RenderCopy(renderer, enemy->healthbar_texture, NULL, &r);
  }
}

void EnemyWrapper::move(Map *curMap) {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  if (movementState == MovementState::WALK) {
    if (xDirection == Direction::LEFT) {
      xPos -= xVel * dT;
      if (xPos < xPosMin ||
          curMap->isInvalidEnemyPosition(ID, xPos, yPos, width, height)) {
        xPos += xVel * dT;
        xDirection = Direction::RIGHT;
        if (xVelRange > 0) {
          xVel = rand() % xVelRange + xVelBase;
        }
      }
    } else {
      xPos += xVel * dT;
      if (xPos > xPosMax ||
          curMap->isInvalidEnemyPosition(ID, xPos, yPos, width, height)) {
        xPos -= xVel * dT;
        xDirection = Direction::LEFT;
        if (xVelRange > 0) {
          xVel = rand() % xVelRange + xVelBase;
        }
      }
    }

    if (yDirection == Direction::UP) {
      yPos -= yVel * dT;
      if (yPos < yPosMin ||
          curMap->isInvalidEnemyPosition(ID, xPos, yPos, width, height)) {
        yPos += yVel * dT;
        yDirection = Direction::DOWN;
        if (yVelRange > 0) {
          yVel = rand() % yVelRange + yVelBase;
        }
      }
    } else {
      yPos += yVel * dT;
      if (yPos > yPosMax ||
          curMap->isInvalidEnemyPosition(ID, xPos, yPos, width, height)) {
        yPos -= yVel * dT;
        yDirection = Direction::UP;
        if (yVelRange > 0) {
          yVel = rand() % yVelRange + yVelBase;
        }
      }
    }
  }

  lastUpdate = current;
}