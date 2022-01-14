#include "inventory.h"

int Inventory::nextID = 0;

Inventory::Inventory(float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating inventory " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
  numRow =
      (height - INVENTORY_BORDER) / (INVENTORY_GRID_SIZE + INVENTORY_BORDER);
  numCol =
      (width - INVENTORY_BORDER) / (INVENTORY_GRID_SIZE + INVENTORY_BORDER);
}

Inventory::~Inventory() {
  if (DEBUG) {
    std::cout << "Destroying inventory " << ID << std::endl;
  }
}

void Inventory::print() {
  std::cout << "Inventory " << ID << std::endl;
  std::cout << "-Current size: " << items.size() << std::endl;
}

bool Inventory::addItem(Logs *logs, Object o, int q) {
  o.isSelected = false;

  if (items.contains(o)) {
    items[o] += q;
    if (items[o] > INVENTORY_PER_ITEM_LIMIT) {
      logs->addLog("-Max quantity per item reached");
      items[o] -= q;
      return false;
    }
  } else {
    if (items.size() < INVENTORY_ITEM_LIMIT) {
      items[o] = q;
    } else {
      logs->addLog("-No more space in bag");
      return false;
    }
  }
  return true;
}

void Inventory::open(Logs *logs) {
  isShowing = true;
  std::string s = "-Right click to sell selected, " +
                  std::string(SDL_GetKeyName(CONFIRM)) + " to use selected";
  logs->addLog(s);
}

void Inventory::close() {
  // unselect
  if (curSelected) {
    curSelected->isSelected = false;
    curSelected = NULL;
  }
  isShowing = false;
}

int Inventory::onClick(Logs *logs, float x, float y, bool isLeft) {
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

void Inventory::onConfirm(Logs *logs) {
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

void Inventory::render(SDL_Renderer *renderer) {
  if (isShowing) {
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(renderer, background, NULL, &r);

    for (int row = 0; row < numRow; row++) {
      for (int col = 0; col < numCol; col++) {
        r.x = xPos + INVENTORY_BORDER +
              col * (INVENTORY_GRID_SIZE + INVENTORY_BORDER);
        r.y = yPos + INVENTORY_BORDER +
              row * (INVENTORY_GRID_SIZE + INVENTORY_BORDER);
        r.w = INVENTORY_GRID_SIZE;
        r.h = INVENTORY_GRID_SIZE;
        SDL_RenderCopy(renderer, texture, NULL, &r);
      }
    }

    int nextR = 0;
    int nextC = 0;
    int offset = (INVENTORY_GRID_SIZE - INVENTORY_OBJECT_SIZE) / 2;
    for (auto &o : items) {
      float x = xPos + INVENTORY_BORDER +
                nextC * (INVENTORY_GRID_SIZE + INVENTORY_BORDER) + offset;
      float y = yPos + INVENTORY_BORDER +
                nextR * (INVENTORY_GRID_SIZE + INVENTORY_BORDER) + offset;

      // item
      o.first.setInventoryPosition(x, y);
      o.first.render(renderer, x, y, INVENTORY_OBJECT_SIZE,
                     INVENTORY_OBJECT_SIZE);

      // quantity
      SDL_Surface *q = TTF_RenderText_Solid(
          font, std::to_string(o.second).c_str(), text_color);
      if (!q) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
      }
      SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, q);
      SDL_Rect r0;
      r0.x = x - offset + INVENTORY_GRID_SIZE - q->w;
      r0.y = y - offset + INVENTORY_GRID_SIZE - q->h;
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

void Inventory::onLeftClick(Logs *logs, float x, float y) {
  for (auto &[i, q] : items) {
    if (i.xPosIL < x && x < i.xPosIL + INVENTORY_OBJECT_SIZE && i.yPosIL < y &&
        y < i.yPosIL + INVENTORY_OBJECT_SIZE) {
      if (!i.isSelected) {
        // unselect previous and select this
        if (curSelected) {
          curSelected->isSelected = false;
        }
        curSelected = &i;

        // TODO: use a UI similar to shop instead of writing to logs
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

int Inventory::onRightClick(Logs *logs, float x, float y) {
  for (auto &[i, q] : items) {
    if (i.xPosIL < x && x < i.xPosIL + INVENTORY_OBJECT_SIZE && i.yPosIL < y &&
        y < i.yPosIL + INVENTORY_OBJECT_SIZE) {
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

bool Inventory::decreaseItem(Object o) {
  if (!items.contains(o)) {
    std::cout << "Item not found in item list" << std::endl;
    return false;
  }
  items[o]--;
  if (items[o] == 0) {
    items.erase(o);
    return false;
  }
  return true;
}