#include "enemy.h"

int Enemy::nextID = 0;

Enemy::Enemy(float xMin, float xMax, float yMin, float yMax,
             MovementState state, int p, int diff, float w, float h, int xVBase,
             int yVBase, int xVRange, int yVRange) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating enemy " << ID << std::endl;
  }

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
  movement = state;

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
  return (xPos < x + w && x < xPos + width && yPos < y + h &&
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
  isAttacked = true; // flag reset after rendering
  hp -= calculateDamage(attack);
  if (hp <= 0) {
    hp = 0;
    isAlive = false;
    // TO-DO: do something? drops?
  }

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
        stillTexture, NULL, NULL, &actualW,
        &actualH); // TO-DO: here assuming all textures have the same size
    s.x = s.x / width * actualW;
    s.y = s.y / height * actualH;
    s.w = actualW - s.x;
    s.h = actualH - s.y;

    SDL_Rect r;
    r.x = std::max(0.0f, round(xPos - camX));
    r.y = std::max(0.0f, round(yPos - camY));
    r.w = width - std::max(0.0f, round(camX - xPos));
    r.h = height - std::max(0.0f, round(camY - yPos));

    // TO-DO: there should be a delay before isAttacked and start of attack
    // animation
    if (!isAttacked) {
      if (movement == MovementState::STILL) {
        SDL_RenderCopy(renderer, stillTexture, &s, &r);
      } else {
        movingIndices[xDirection].second++;
        if (movingIndices[xDirection].second > ENEMY_PER_FRAME_LENGTH) {
          // switch to next frame
          movingIndices[xDirection].second = 0;
          movingIndices[xDirection].first =
              (movingIndices[xDirection].first + 1) %
              (movingTextures[xDirection].size());
        }
        SDL_RenderCopy(
            renderer,
            movingTextures[xDirection][movingIndices[xDirection].first], &s,
            &r);
      }
    } else {
      attackIndices[xDirection].second++;
      if (attackIndices[xDirection].second > ENEMY_PER_FRAME_LENGTH) {
        // switch to next frame
        attackIndices[xDirection].second = 0;
        attackIndices[xDirection].first =
            (attackIndices[xDirection].first + 1) %
            (attackTextures[xDirection].size());
      }
      SDL_RenderCopy(
          renderer, attackTextures[xDirection][attackIndices[xDirection].first],
          &s, &r);
    }
  } else {
    // TO-DO: death animation?
  }
}

int Enemy::calculateDamage(int attack) {
  return attack * (2 - (difficulty / ENEMY_MAX_DIFFICULTY));
}

// TO-DO: right now may move into other objects on the map
void Enemy::move() {
  Uint32 current = SDL_GetTicks();
  float dT = (current - lastUpdate) / 1000.0f;

  if (movement == MovementState::WALK && !isAttacked && isAlive) {
    if (xDirection == Direction::LEFT) {
      xPos -= xVel * dT;
      if (xPos < xPosMin) {
        xPos += xVel * dT;
        xDirection = Direction::RIGHT;
        xVel = rand() % xVelRange + xVelBase;
      }
    } else {
      xPos += xVel * dT;
      if (xPos > xPosMax) {
        xPos -= xVel * dT;
        xDirection = Direction::LEFT;
        xVel = rand() % xVelRange + xVelBase;
      }
    }

    if (yDirection == Direction::UP) {
      yPos -= yVel * dT;
      if (yPos < yPosMin) {
        yPos += yVel * dT;
        yDirection = Direction::DOWN;
        yVel = rand() % yVelRange + yVelBase;
      }
    } else {
      yPos += yVel * dT;
      if (yPos > yPosMax) {
        yPos -= yVel * dT;
        yDirection = Direction::UP;
        yVel = rand() % yVelRange + yVelBase;
      }
    }
  }

  lastUpdate = current;
}