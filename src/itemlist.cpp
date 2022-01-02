#include "itemlist.h"

int Itemlist::nextID = 0;

Itemlist::Itemlist(float x, float y, float w, float h, float g, float o,
                   int l) {
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
  numRow = floor(height / grid_size);
  numCol = floor(width / grid_size);

  limit = l;
  std::vector<Object> items;
}

Itemlist::~Itemlist() {
  if (DEBUG) {
    std::cout << "Destroying itemlist " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
}

void Itemlist::print() {
  std::cout << "Itemlist " << ID << std::endl;
  std::cout << "-Current size: " << curSize << std::endl;
}

void Itemlist::addItem(Object o) {
  if (curSize + 1 <= limit) {
    curSize++;
    items.push_back(o);
  } else {
    // TO-DO: display message
    std::cout << "No more space in bag" << std::endl;
  }
}

void Itemlist::onClick(float x, float y, bool isLeft) {
  if (isLeft) {
    onLeftClick(x, y);
  } else {
    onRightClick(x, y);
  }
}

void Itemlist::render(SDL_Renderer *renderer) {
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
      float x = xPos + nextC * grid_size + offset;
      float y = yPos + nextR * grid_size + offset;
      o.setItemlistPosition(x, y);
      o.render(renderer, x, y, object_size, object_size);

      if (nextC + 1 < numCol) {
        nextC++;
      } else if (nextR + 1 < numRow) {
        nextC = 0;
        nextR++;
      }
    }
  }
}

void Itemlist::onLeftClick(float x, float y) {
  if (!isShowing) {
    return;
  }
  for (auto &i : items) {
    if (i.xPosIL < x && x < i.xPosIL + object_size && i.yPosIL < y &&
        y < i.yPosIL + object_size) {
      if (DEBUG) {
        std::cout << "Left clicking on item " << i.ID << std::endl;
      }

      if (!i.isSelected) {
        // unselect previous and select this
        if (curSelected) {
          curSelected->isSelected = false;
        }
        curSelected = &i;

        // TO-DO: item clicked, show actions
        std::cout << "Right click to use item" << std::endl;
      } else {
        // unselect this
        curSelected = NULL;
      }
      i.isSelected = !i.isSelected;
    }
  }
}

void Itemlist::onRightClick(float x, float y) {
  if (!isShowing) {
    return;
  }

  for (auto &i : items) {
    if (i.xPosIL < x && x < i.xPosIL + object_size && i.yPosIL < y &&
        y < i.yPosIL + object_size) {
      if (DEBUG) {
        std::cout << "Right clicking on item " << i.ID << std::endl;
      }

      if (i.isSelected) {
        // use item, remove and unselect if used
        if (i.onUse()) {
          i.isSelected = !i.isSelected;
          removeItem(i);
          curSelected = NULL;
        }
      }
    }
  }
}

void Itemlist::removeItem(Object o) {
  curSize--;
  items.erase(std::remove(items.begin(), items.end(), o), items.end());
}