#include "itemlist.h"

int Itemlist::nextID = 0;

Itemlist::Itemlist(float x, float y, float w, float h, float g, float o,
                   float b, int l, int pl) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating itemlist " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
  grid_size = g;
  object_size = o;
  border = b;
  numRow = (height - border) / (grid_size + border);
  numCol = (width - border) / (grid_size + border);

  limit = l;
  perLimit = pl;
}

Itemlist::~Itemlist() {
  if (DEBUG) {
    std::cout << "Destroying itemlist " << ID << std::endl;
  }
}

void Itemlist::print() {
  std::cout << "Itemlist " << ID << std::endl;
  std::cout << "-Current size: " << curSize << std::endl;
}

bool Itemlist::addItem(Logs *logs, Object o, int q) {
  o.isSelected = false;
  if (items.contains(o)) {
    items[o] += q;
    if (items[o] > perLimit) {
      logs->addLog("Max quantity per item reached");
      items[o] -= q;
      return false;
    }
  } else {
    if (curSize + 1 <= limit) {
      curSize++;
      items[o] = q;
    } else {
      logs->addLog("No more space in bag");
      return false;
    }
  }
  return true;
}
void Itemlist::useItem(Object o){};

void Itemlist::open(Logs *logs) {
  isShowing = true;
  std::string s = "-Right click to sell selected, " +
                  std::string(SDL_GetKeyName(CONFIRM)) + " to use selected";
  logs->addLog(s);
}

void Itemlist::close() {
  // unselect
  if (curSelected) {
    curSelected->isSelected = false;
    curSelected = NULL;
  }
  isShowing = false;
}

int Itemlist::onClick(Logs *logs, float x, float y, bool isLeft) {
  if (!isShowing) {
    return 0;
  }

  if (isLeft) {
    onLeftClick(logs, x, y);
    return 0;
  } else {
    return onRightClick(logs, x, y);
  }
}

void Itemlist::onConfirm(Logs *logs) {
  if (!isShowing) {
    return;
  }

  if (curSelected) {
    // use item, decrease quantity if used, unselect if no more left
    if (curSelected->onUse()) {
      std::string s = "-Used " + curSelected->name;
      logs->addLog(s);
      bool flag = decreaseItem(*curSelected);
      if (!flag) {
        curSelected->isSelected = !curSelected->isSelected;
        curSelected = NULL;
      }
    }
  }
}

void Itemlist::render(SDL_Renderer *renderer) {
  if (isShowing) {
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(renderer, background, NULL, &r);

    for (int row = 0; row < numRow; row++) {
      for (int col = 0; col < numCol; col++) {
        r.x = xPos + border + col * (grid_size + border);
        r.y = yPos + +border + row * (grid_size + border);
        r.w = grid_size;
        r.h = grid_size;
        SDL_RenderCopy(renderer, texture, NULL, &r);
      }
    }

    int nextR = 0;
    int nextC = 0;
    int offset = (grid_size - object_size) / 2;
    // TO-DO: maybe use something ordered to preserve order?
    for (auto &o : items) {
      float x = xPos + border + nextC * (grid_size + border) + offset;
      float y = yPos + border + nextR * (grid_size + border) + offset;

      // item
      o.first.setItemlistPosition(x, y);
      o.first.render(renderer, x, y, object_size, object_size);

      // quantity
      SDL_Surface *q = TTF_RenderText_Solid(
          font, std::to_string(o.second).c_str(), text_color);
      if (!q) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
      }
      SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, q);
      SDL_Rect r0;
      r0.x = x - offset + grid_size - q->w;
      r0.y = y - offset + grid_size - q->h;
      r0.w = q->w;
      r0.h = q->h;
      SDL_RenderCopy(renderer, t, NULL, &r0);
      SDL_FreeSurface(q);
      SDL_DestroyTexture(t);

      if (nextC + 1 < numCol) {
        nextC++;
      } else if (nextR + 1 < numRow) {
        nextC = 0;
        nextR++;
      }
    }
  }
}

void Itemlist::onLeftClick(Logs *logs, float x, float y) {
  for (auto &[i, q] : items) {
    if (i.xPosIL < x && x < i.xPosIL + object_size && i.yPosIL < y &&
        y < i.yPosIL + object_size) {
      if (!i.isSelected) {
        // unselect previous and select this
        if (curSelected) {
          curSelected->isSelected = false;
        }
        curSelected = &i;

        std::string s =
            "-Selected item: " + i.name + ", value: " + std::to_string(i.value);
        logs->addLog(s);
      } else {
        // unselect this
        curSelected = NULL;
      }
      i.isSelected = !i.isSelected;
    }
  }
}

int Itemlist::onRightClick(Logs *logs, float x, float y) {
  for (auto &[i, q] : items) {
    if (i.xPosIL < x && x < i.xPosIL + object_size && i.yPosIL < y &&
        y < i.yPosIL + object_size) {
      if (i.isSelected && i.type != ObjectType::QUEST_OBJECT) {
        std::string s = "-Sold " + i.name + " for " + std::to_string(i.value);
        logs->addLog(s);
        // decrease and unselect if none remaining
        bool flag = decreaseItem(i);
        if (!flag) {
          i.isSelected = !i.isSelected;
          curSelected = NULL;
        }
        return i.value;
      } else if (i.type == ObjectType::QUEST_OBJECT) {
        logs->addLog("-Cannot sell a quest item");
      }
    }
  }

  return 0;
}

bool Itemlist::decreaseItem(Object o) {
  if (!items.contains(o)) {
    std::cout << "Item not found in item list" << std::endl;
    return false;
  }
  items[o]--;
  if (items[o] == 0) {
    curSize--;
    items.erase(o);
    return false;
  }
  return true;
}