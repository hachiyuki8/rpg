#include "convo.h"

int Convo::nextID = 0;

Convo::Convo(float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating convo " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
}

Convo::~Convo() {
  if (DEBUG) {
    std::cout << "Destroying convo " << ID << std::endl;
  }
  for (auto &ls : allLines) {
    for (auto &l : ls.line_texts) {
      SDL_FreeSurface(l);
    }
  }
}

void Convo::print() {
  std::cout << "Convo " << ID << std::endl;
  std::cout << "-Number of lines: " << allLines.size() << ", currently at "
            << curIndex << std::endl;
}

void Convo::init(std::vector<std::tuple<int, std::vector<std::string>>> lines) {
  for (auto &ls : lines) {
    int index = std::get<0>(ls);
    std::vector<std::string> lines = std::get<1>(ls);

    struct Line newL;
    if (index < 0) {
      newL.icon = playerIcon;
    } else {
      newL.icon = npcTextures[index];
    }

    for (auto &l : lines) {
      newL.lines.push_back(l);
      SDL_Surface *line_text = TTF_RenderText_Blended_Wrapped(
          font, l.c_str(), text_color, CONVO_WIDTH);
      if (!line_text) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
      }
      newL.line_texts.push_back(line_text);
    }
    allLines.push_back(newL);
  }
}

void Convo::clear() {
  for (auto &ls : allLines) {
    for (auto &l : ls.line_texts) {
      SDL_FreeSurface(l);
    }
  }
  allLines.clear();
}

void Convo::open() {
  isShowing = true;
  curIndex = 0;
}

void Convo::close() { isShowing = false; }

bool Convo::next() {
  curIndex++;
  if (curIndex >= allLines.size()) {
    close();
    return false;
  }

  return true;
}

void Convo::render(SDL_Renderer *renderer) {
  if (isShowing) {
    // background
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &r);

    // speaker icon
    r.x = xPos + border;
    r.y = yPos + border;
    r.w = iconSize;
    r.h = iconSize;
    SDL_RenderCopy(renderer, allLines[curIndex].icon, NULL, &r);

    // text
    r.x = xPos + border + offsetLeft;
    for (auto &l : allLines[curIndex].line_texts) {
      r.w = l->w;
      r.h = l->h;
      SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, l);
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_DestroyTexture(t);
      r.y += l->h + lineHeight;
    }
  }
}