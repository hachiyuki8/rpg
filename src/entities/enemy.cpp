#include "enemy.h"

int Enemy::nextID = 0;

Enemy::Enemy(float xMin, float xMax, float yMin, float yMax, std::string n,
             MovementState state, int p, int diff, float w, float h, int xVBase,
             int yVBase, int xVRange, int yVRange) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating enemy " << ID << std::endl;
  }

  name = n;
  stillTextures = AssetManager::enemyTextures[name][MovementState::STILL];
  movingTextures = AssetManager::enemyTextures[name][MovementState::WALK];
  attackTextures = AssetManager::enemyTextures[name][MovementState::ATTACK];

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

  hp = p;
  difficulty = diff;
  movementState = state;

  lastUpdate = SDL_GetTicks();
}

Enemy::~Enemy() {
  if (DEBUG) {
    std::cout << "Destroying enemy " << ID << std::endl;
  }
}

void Enemy::print() {
  std::cout << "Enemy " << ID << std::endl;
  std::cout << "-HP: " << hp << ", difficulty: " << difficulty << std::endl;
}

bool Enemy::isInvalidPosition(float x, float y, float w, float h) {
  return (isAlive && xPos < x + w && x < xPos + width && yPos < y + h &&
          y < yPos + height);
}

void Enemy::addReward(Object o, int q) {
  rewards.push_back(std::make_tuple(o, q));
}

bool Enemy::isInRange(float x, float y, float w, float h) {
  return (xPos - ENEMY_INTERACTION_RANGE <= x + w &&
          x <= xPos + width + ENEMY_INTERACTION_RANGE &&
          yPos - ENEMY_INTERACTION_RANGE <= y + h &&
          y <= yPos + height + ENEMY_INTERACTION_RANGE);
}

std::pair<int, int> Enemy::onAttack(float x, int attack) {
  if (movementState == MovementState::ATTACK) {
    return std::make_pair(-1, -1);
  }

  oldMovementState = movementState;
  movementState = MovementState::ATTACK;
  hp -= calculateDamage(attack);
  if (hp <= 0) {
    hp = 0;
    isAlive = false;
  }

  std::cout << "HP: " << hp << std::endl;

  if (x > xPos + width / 2) {
    xDirection = Direction::RIGHT;
  } else {
    xDirection = Direction::LEFT;
  }
  return std::make_pair(difficulty, isAlive);
}

void Enemy::render(SDL_Renderer *renderer, float camX, float camY, float camW,
                   float camH) {
  move();

  if (xPos + width < camX || xPos > camX + camW || yPos + height < camY ||
      yPos > camY + camH) {
    return;
  }

  if (isAlive) {
    SDL_Rect s;
    s.x = std::max(0.0f, round(camX - xPos));
    s.y = std::max(0.0f, round(camY - yPos));
    // rescale
    int actualW, actualH;
    SDL_QueryTexture(
        stillTextures[Direction::LEFT][0], NULL, NULL, &actualW,
        &actualH); // TODO: here assuming all textures have the same size
    s.x = s.x / width * actualW;
    s.y = s.y / height * actualH;
    s.w = actualW - s.x;
    s.h = actualH - s.y;

    SDL_Rect r;
    r.x = std::max(0.0f, round(xPos - camX));
    r.y = std::max(0.0f, round(yPos - camY));
    r.w = width - std::max(0.0f, round(camX - xPos));
    r.h = height - std::max(0.0f, round(camY - yPos));

    // TODO: there should be a delay before attacked and start of attack
    // animation
    switch (movementState) {
    case MovementState::STILL:
      stillIndices[xDirection].second++;
      if (stillIndices[xDirection].second > ENEMY_PER_FRAME_LENGTH) {
        // switch to next frame
        stillIndices[xDirection].second = 0;
        stillIndices[xDirection].first = (stillIndices[xDirection].first + 1) %
                                         (stillTextures[xDirection].size());
      }
      SDL_RenderCopy(renderer,
                     stillTextures[xDirection][stillIndices[xDirection].first],
                     &s, &r);
      break;
    case MovementState::WALK:
      movingIndices[xDirection].second++;
      if (movingIndices[xDirection].second > ENEMY_PER_FRAME_LENGTH) {
        // switch to next frame
        movingIndices[xDirection].second = 0;
        movingIndices[xDirection].first =
            (movingIndices[xDirection].first + 1) %
            (movingTextures[xDirection].size());
      }
      SDL_RenderCopy(
          renderer, movingTextures[xDirection][movingIndices[xDirection].first],
          &s, &r);
      break;
    case MovementState::ATTACK:
      attackIndices[xDirection].second++;
      if (attackIndices[xDirection].second > ENEMY_PER_FRAME_LENGTH) {
        // switch to next frame
        attackIndices[xDirection].second = 0;
        attackIndices[xDirection].first =
            (attackIndices[xDirection].first + 1) %
            (attackTextures[xDirection].size());

        if (attackIndices[xDirection].first == 0) {
          movementState = oldMovementState;
        }
      }
      SDL_RenderCopy(
          renderer, attackTextures[xDirection][attackIndices[xDirection].first],
          &s, &r);
    default:
      break;
    }

  } else {
    // TODO: death animation?
  }
}

int Enemy::calculateDamage(int attack) {
  return attack * (2 - (difficulty / ENEMY_MAX_DIFFICULTY)); // TODO: not sure
}

// TODO: right now may move into other objects on the map including the player
void Enemy::move() {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  if (movementState == MovementState::WALK && isAlive) {
    if (xDirection == Direction::LEFT) {
      xPos -= xVel * dT;
      if (xPos < xPosMin) {
        xPos += xVel * dT;
        xDirection = Direction::RIGHT;
        if (xVelRange > 0) {
          xVel = rand() % xVelRange + xVelBase;
        }
      }
    } else {
      xPos += xVel * dT;
      if (xPos > xPosMax) {
        xPos -= xVel * dT;
        xDirection = Direction::LEFT;
        if (xVelRange > 0) {
          xVel = rand() % xVelRange + xVelBase;
        }
      }
    }

    if (yDirection == Direction::UP) {
      yPos -= yVel * dT;
      if (yPos < yPosMin) {
        yPos += yVel * dT;
        yDirection = Direction::DOWN;
        if (yVelRange > 0) {
          yVel = rand() % yVelRange + yVelBase;
        }
      }
    } else {
      yPos += yVel * dT;
      if (yPos > yPosMax) {
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