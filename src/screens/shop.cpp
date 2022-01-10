#include "shop.h"
#include "../entities/character.h"

int Shop::nextID = 0;

Shop::Shop(float x, float y, float w, float h, float g, float o, float b,
           float p, int pl) {
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
  border = b;
  panelWidth = p;
  numRow = (height - border) / (grid_size + border);
  numCol = (width - border - panelWidth) / (grid_size + border);

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
  return true;
}

void Shop::open(Logs *logs) {
  isShowing = true;
  std::string s =
      "-Press " + std::string(SDL_GetKeyName(CONFIRM)) + " to buy selected";
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
    // background
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(renderer, background, NULL, &r);

    // grids
    for (int row = 0; row < numRow; row++) {
      for (int col = 0; col < numCol; col++) {
        r.x = xPos + border + col * (grid_size + border);
        r.y = yPos + border + row * (grid_size + border);
        r.w = grid_size;
        r.h = grid_size;
        SDL_RenderCopy(renderer, texture, NULL, &r);
      }
    }

    int nextR = 0;
    int nextC = 0;
    int offset = (grid_size - object_size) / 2;
    for (auto &o : items) {
      float x = xPos + border + nextC * (grid_size + border) + offset;
      float y = yPos + border + nextR * (grid_size + border) + offset;

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

    // selected
    if (curSelected) {
      float x = xPos + width - border * 2 - panelWidth +
                (panelWidth - SHOP_SELECTED_SIZE) / 2;
      float y = yPos + border + SHOP_SELECTED_SIZE;
      float w = SHOP_SELECTED_SIZE;
      float h = SHOP_SELECTED_SIZE;
      curSelected->render(renderer, x, y, w, h);
      // description
      std::string s = curSelected->name + ": " + curSelected->description;
      SDL_Surface *d = TTF_RenderText_Solid(font, s.c_str(), text_color);
      if (!d) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
      }
      SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, d);
      r.x = xPos + width - border - panelWidth;
      r.y = yPos + border + SHOP_SELECTED_SIZE * 3;
      r.w = d->w;
      r.h = d->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_FreeSurface(d);
      SDL_DestroyTexture(t);
    }
  }
}