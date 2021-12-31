#include "map.h"

int Map::nextID = 0;

Map::Map(std::vector<SDL_Texture *> tileTextures, float w, float h, float s) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating map " << ID << std::endl;
  }

  width = w;
  height = h;
  tileSize = s;
  // TO-DO: map initialization is hardcoded now
  for (int row = 0; row < height / tileSize; row++) {
    std::vector<Tile> vec;
    for (int col = 0; col < width / tileSize; col++) {
      if (row == 0 || row + 1 >= height / tileSize || col == 0 ||
          col + 1 >= width / tileSize) {
        Tile t(tileTextures[1], col * tileSize, row * tileSize, tileSize,
               TileState::UNREACHABLE);
        vec.push_back(t);
      } else {
        Tile t(tileTextures[0], col * tileSize, row * tileSize, tileSize,
               TileState::REACHABLE);
        vec.push_back(t);
      }
    }
    tiles.push_back(vec);
  }
}

Map::~Map() {
  if (DEBUG) {
    std::cout << "Destroying map " << ID << std::endl;
  }
}

void Map::print() {
  std::cout << "Map " << ID << std::endl;
  std::cout << "-" << tiles.size() << "*" << tiles[0].size() << " tiles"
            << std::endl;
}

void Map::addObject(Object o) { objects.push_back(o); }

void Map::removeObject(Object o) {
  objects.erase(std::remove(objects.begin(), objects.end(), o), objects.end());
}

bool Map::isInvalidPosition(float x, float y, float w, float h) {
  for (auto &ts : tiles) {
    for (auto &t : ts) {
      if (t.isInvalidPosition(x, y, w, h)) {
        return true;
      }
    }
  }

  for (auto &o : objects) {
    if (o.isInvalidPosition(x, y, w, h)) {
      return true;
    }
  }

  return false;
}

void Map::render(SDL_Renderer *renderer) {
  for (auto &ts : tiles) {
    for (auto &t : ts) {
      t.render(renderer);
    }
  }

  for (auto &o : objects) {
    o.render(renderer);
  }
}