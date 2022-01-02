#include "map.h"

int Map::nextID = 0;

// mapfile must have dimension (w/s) * (h/s)
Map::Map(std::vector<SDL_Texture *> tileTextures,
         std::vector<std::vector<int>> mapfile, float w, float h, float s) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating map " << ID << std::endl;
  }

  width = w;
  height = h;
  tileSize = s;

  for (int row = 0; row < height / tileSize; row++) {
    std::vector<Tile> vec;
    for (int col = 0; col < width / tileSize; col++) {
      Tile t(tileTextures[mapfile[row][col]], col * tileSize, row * tileSize,
             tileSize, TileState::REACHABLE);
      vec.push_back(t);
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

void Map::onInteract(float x, float y, float w, float h) {
  for (auto &ts : tiles) {
    for (auto &t : ts) {
      if (t.onInteract(x, y, w, h)) {
        return; // TO-DO: only interact with one? or maybe multiple
      }
    }
  }

  for (auto &o : objects) {
    if (o.onInteract(x, y, w, h)) {
      return;
    }
  }
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

std::pair<int, int> Map::findTileIndex(float x, float y) {
  if (DEBUG) {
    std::cout << "x: " << x << ", y: " << y << std::endl;
    std::cout << "index (" << floor(y / tileSize) << ", " << floor(x / tileSize)
              << ")" << std::endl;
  }
  return std::make_pair(floor(y / tileSize), floor(x / tileSize));
}