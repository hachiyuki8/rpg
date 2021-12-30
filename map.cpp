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
  for (int row = 0; row < height / tileSize; row++) {
    std::vector<Tile> vec;
    for (int col = 0; col < width / tileSize; col++) {
      Tile t(tileTextures[0], col * TILE_SIZE, row * TILE_SIZE);
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

void Map::render(SDL_Renderer *renderer) {
  for (auto &ts : tiles) {
    for (auto &t : ts) {
      t.render(renderer);
    }
  }
}