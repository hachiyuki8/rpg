#include "characterNPC.h"

#include "character.h"

int CharacterNPC::nextID = 0;

CharacterNPC::CharacterNPC(SDL_Texture *t, NPCState st, float x, float y,
                           float w, float h) {
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

bool CharacterNPC::isInvalidPosition(float x, float y, float w, float h) {
  return (xPos < x + w && x < xPos + width && yPos < y + h &&
          y < yPos + height);
}

bool CharacterNPC::onInteract(Character *curPlayer, float x, float y, float w,
                              float h) {
  if (!isInRange(x, y, w, h)) {
    return false;
  }

  switch (state) {
    case NPCState::SHOP_NPC:
      if (curPlayer->uiState == UIState::IN_GAME) {
        shop.open(&curPlayer->logs);
        curPlayer->uiState = UIState::IN_SHOP;
        curPlayer->curNPC = this;
      }
      return true;
    case NPCState::CONVO_NPC:
      if (curPlayer->uiState == UIState::IN_GAME) {
        convo.open();
        curPlayer->uiState = UIState::IN_CONVO;
        curPlayer->curNPC = this;
      }
      return true;
    default:  // TODO: other NPC types
      break;
  }

  return false;
}

void CharacterNPC::onQuit() {
  switch (state) {
    case NPCState::SHOP_NPC:
      shop.close();
      break;
    case NPCState::CONVO_NPC:
      convo.close();
      break;
    default:
      break;
  }
}

void CharacterNPC::onClick(float x, float y) {
  switch (state) {
    case NPCState::SHOP_NPC:
      shop.onClick(x, y);
      break;
    default:
      break;
  }
}

bool CharacterNPC::onConfirm(Character *curPlayer) {
  switch (state) {
    case NPCState::SHOP_NPC:
      shop.onConfirm(curPlayer);
      return true;
    case NPCState::CONVO_NPC:
      return convo.next();
    default:
      return true;
  }
}

void CharacterNPC::setConvo(
    std::vector<std::tuple<std::string, std::vector<std::string>>> lines) {
  if (state != NPCState::CONVO_NPC) {
    std::cout << "Cannot set conversation for non CONVO_NPC" << std::endl;
    return;
  }
  convo.clear();
  convo.init(lines);
}

void CharacterNPC::addToShop(std::vector<std::tuple<Object, int>> items) {
  if (state != NPCState::SHOP_NPC) {
    std::cout << "Cannot add shop items for non SHOP_NPC" << std::endl;
    return;
  }
  for (auto &t : items) {
    shop.addItem(std::get<0>(t), std::get<1>(t));
  }
}

void CharacterNPC::render(SDL_Renderer *renderer, float camX, float camY,
                          float camW, float camH) {
  if (xPos + width < camX || xPos > camX + camW || yPos + height < camY ||
      yPos > camY + camH) {
    return;
  }

  SDL_Rect s;
  s.x = std::max(0.0f, round(camX - xPos));
  s.y = std::max(0.0f, round(camY - yPos));
  // rescale
  int actualW, actualH;
  SDL_QueryTexture(texture, NULL, NULL, &actualW, &actualH);
  s.x = s.x / width * actualW;
  s.y = s.y / height * actualH;
  s.w = actualW - s.x;
  s.h = actualH - s.y;

  SDL_Rect r;
  r.x = std::max(0.0f, round(xPos - camX));
  r.y = std::max(0.0f, round(yPos - camY));
  r.w = width - std::max(0.0f, round(camX - xPos));
  r.h = height - std::max(0.0f, round(camY - yPos));

  SDL_RenderCopy(renderer, texture, &s, &r);

  shop.render(renderer);
  convo.render(renderer);
}

void CharacterNPC::renderScreen(SDL_Renderer *renderer) {
  switch (state) {
    case NPCState::SHOP_NPC:
      shop.render(renderer);
      break;
    case NPCState::CONVO_NPC:
      convo.render(renderer);
      break;
    default:
      break;
  }
}

bool CharacterNPC::isInRange(float x, float y, float w, float h) {
  return (xPosI <= x + w && x <= xPosI + widthI && yPosI <= y + h &&
          y <= yPosI + heightI);
}