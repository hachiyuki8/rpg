#include "characterNPC.h"
#include "character.h"

int CharacterNPC::nextID = 0;

CharacterNPC::CharacterNPC(SDL_Texture *t, SDL_Texture *shop_t, TTF_Font *f,
                           PlayerState st, float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating characterNPC " << ID << std::endl;
  }

  texture = t;
  xPos = x;
  yPos = y;
  width = w;
  height = h;
  state = st;

  xPosI = x;
  yPosI = y;
  widthI = w;
  heightI = h;

  if (state == PlayerState::SHOP_NPC) {
    shop.texture = shop_t;
    shop.font = f;
  }
}

CharacterNPC::~CharacterNPC() {
  if (DEBUG) {
    std::cout << "Destroying characterNPC " << ID << std::endl;
  }
}

void CharacterNPC::print() {
  std::cout << "CharacterNPC " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

void CharacterNPC::setInteractRange(float left, float right, float up,
                                    float down) {
  xPosI = xPos - left;
  widthI = width + left + right;
  yPosI = yPos - up;
  heightI = height + up + down;
}

bool CharacterNPC::onInteract(Character *curPlayer, float x, float y, float w,
                              float h) {
  if (!isInRange(x, y, w, h)) {
    return false;
  }

  switch (state) {
  case PlayerState::SHOP_NPC:
    switch (curPlayer->uiState) {
    case UIState::IN_GAME:
      shop.open(&curPlayer->logs);
      curPlayer->uiState = UIState::IN_SHOP;
      curPlayer->curShop = &shop;
      break;
    case UIState::IN_SHOP:
      shop.close();
      curPlayer->uiState = UIState::IN_GAME;
      curPlayer->curShop = NULL;
      break;
    default:
      break;
    }
    return true;
  default: // TO-DO: other NPC types
    break;
  }

  return false;
}

void CharacterNPC::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}

bool CharacterNPC::isInRange(float x, float y, float w, float h) {
  return (xPosI <= x + w && x <= xPosI + widthI && yPosI <= y + h &&
          y <= yPosI + heightI);
}