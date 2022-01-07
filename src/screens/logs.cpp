#include "logs.h"

int Logs::nextID = 0;

Logs::Logs(float x, float y, float w, float h, int l) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating logs " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;

  lineLimit = l;
  lineHeight = (height - offset * 2) / lineLimit;
}

Logs::~Logs() {
  if (DEBUG) {
    std::cout << "Destroying logs " << ID << std::endl;
  }
  for (auto &l : logs) {
    SDL_FreeSurface(l.text);
  }
}

void Logs::print() {
  std::cout << "Logs " << ID << std::endl;
  std::cout << "-curSize: " << curSize << std::endl;
}

void Logs::addLog(std::string s) {
  struct Log l;
  l.content = s;
  SDL_Surface *text = TTF_RenderText_Solid(font, s.c_str(), text_color);
  if (!text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  l.text = text;
  logs.push_back(l);
  curSize++;
  if (curSize > lineLimit) {
    SDL_FreeSurface(logs.front().text);
    logs.pop_front();
  }
}

void Logs::toggleShow() { isShowing = !isShowing; }

void Logs::render(SDL_Renderer *renderer) {
  if (isShowing) {
    // background
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, 200);
    SDL_RenderCopy(renderer, texture, NULL, &r);

    r.x += offset;
    r.y += offset;

    // logs
    for (auto &l : logs) {
      SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, l.text);
      r.w = l.text->w;
      r.h = l.text->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_DestroyTexture(t);
      r.y += lineHeight;
    }
  }
}