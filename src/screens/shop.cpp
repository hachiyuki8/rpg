#include "shop.h"
#include "../entities/character.h"

int Shop::nextID = 0;

Shop::Shop(float x, float y, float w, float h, float g, float o, int pl) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating shop " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
  grid_size = g;
  object_size = o;
  numRow = floor(height / grid_size);
  numCol = floor(width / grid_size);

  perLimit = pl;
}

Shop::~Shop() {
  if (DEBUG) {
    std::cout << "Destroying shop " << ID << std::endl;
  }
}

void Shop::print() { std::cout << "Shop " << ID << std::endl; }

bool Shop::addItem(Object o, int q) {
  if (items.contains(o)) {
    items[o] += q;
    if (items[o] > perLimit) {
      std::cout << "Max quantity per item reached" << std::endl;
      items[o] -= q;
      return false;
    }
  } else {
    if (items.size() + 1 <= numRow * numCol) {
      items[o] = q;
    } else {
      std::cout << "No more space in shop" << std::endl;
      return false;
    }
  }
  std::cout << items.size() << std::endl;
  return true;
}

void Shop::open(Logs *logs) {
  isShowing = true;
  std::string s =
      "Press " + std::string(SDL_GetKeyName(CONFIRM)) + " to use selected";
  logs->addLog(s);
}

void Shop::close() {
  // unselect
  if (curSelected) {
    curSelected->isSelected = false;
    curSelected = NULL;
  }
  isShowing = false;
}

void Shop::onClick(Logs *logs, float x, float y) {
  if (!isShowing) {
    return;
  }

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
            "-Selected item: " + i.name + ", cost: " + std::to_string(i.value);
        logs->addLog(s);
      } else {
        // unselect this
        curSelected = NULL;
      }
      i.isSelected = !i.isSelected;
    }
  }
}

void Shop::onConfirm(Character *curPlayer) {
  if (!isShowing) {
    return;
  }

  if (curSelected) {
    if (!items.contains(*curSelected)) {
      std::cout << "Item not found in shop" << std::endl;
      return;
    }
    if (curPlayer->stats.decreaseMoneyIfEnough(&curPlayer->logs,
                                               curSelected->value) &&
        curPlayer->itemlist.addItem(&curPlayer->logs, *curSelected, 1)) {
      std::string s = "-Bought " + curSelected->name;
      curPlayer->logs.addLog(s);
      items[*curSelected]--;
      if (items[*curSelected] == 0) {
        items.erase(*curSelected);
        curSelected = NULL;
      }
    }
  }
  return;
}

void Shop::render(SDL_Renderer *renderer) {
  if (isShowing) {
    for (int row = 0; row < numRow; row++) {
      for (int col = 0; col < numCol; col++) {
        SDL_Rect r;
        r.x = xPos + col * grid_size;
        r.y = yPos + row * grid_size;
        r.w = grid_size;
        r.h = grid_size;
        SDL_RenderCopy(renderer, texture, NULL, &r);
      }
    }

    int nextR = 0;
    int nextC = 0;
    int offset = (grid_size - object_size) / 2;
    for (auto &o : items) {
      std::cout << ">>>" << std::endl;
      float x = xPos + nextC * grid_size + offset;
      float y = yPos + nextR * grid_size + offset;

      // item
      o.first.setItemlistPosition(x, y); // TO-DO: reusing the same parameters
                                         // as Itemlist, may separate these two?
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