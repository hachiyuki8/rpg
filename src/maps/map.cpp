#include "map.h"

int Map::nextID = 0;

Map::Map(std::vector<std::vector<int>> mapfile, float w, float h, float s) {
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
      int index = mapfile[row][col];
      if (index >= 0) {
        Tile t(tileTextures[index], col * tileSize, row * tileSize, tileSize,
               TileState::REACHABLE);
        vec.push_back(t);
      } else {
        Tile t(tileTextures[-index], col * tileSize, row * tileSize, tileSize,
               TileState::UNREACHABLE);
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

void Map::addTeleporter(Teleporter tp) { teleporters.push_back(tp); }

void Map::addObject(Object o) { objects.push_back(o); }

void Map::removeObject(Object o) {
  objects.erase(std::remove(objects.begin(), objects.end(), o), objects.end());
}

void Map::addNPC(CharacterNPC *npc) { NPCs.push_back(npc); }

bool Map::isInvalidPosition(float x, float y, float w, float h) {
  if (x < 0 || x + w > width || y < 0 || y + h > height) {
    return true;
  }

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

  for (auto &npc : NPCs) {
    if (npc->isInvalidPosition(x, y, w, h)) {
      return true;
    }
  }

  return false;
}

std::tuple<Map *, float, float> Map::onInteract(Character *curPlayer,
                                                Map *curMap, float x, float y,
                                                float w, float h) {
  for (auto &npc : NPCs) {
    if (npc->onInteract(curPlayer, x, y, w, h)) {
      return std::make_tuple(curMap, x, y);
    }
  }

  for (auto &tp : teleporters) {
    if (tp.src_map == curMap) {
      for (auto &sd : tp.srcToDest) {
        if (tiles[sd.first.first][sd.first.second].isInTile(x, y, w, h)) {
          // change map and return new tile center
          return std::make_tuple(
              tp.dest_map,
              tp.dest_map->tiles[sd.second.first][sd.second.second].xPos +
                  tileSize / 2,
              tp.dest_map->tiles[sd.second.first][sd.second.second].yPos +
                  tileSize / 2);
        }
      }
    }
  }

  for (auto &o : objects) {
    if (o.onInteract(x, y, w, h)) {
      return std::make_tuple(curMap, x, y);
    }
  }

  return std::make_tuple(curMap, x, y);
}

void Map::render(SDL_Renderer *renderer, float camX, float camY, float camW,
                 float camH) {
  for (auto &ts : tiles) {
    for (auto &t : ts) {
      t.render(renderer, camX, camY, camW, camH);
    }
  }

  for (auto &o : objects) {
    o.render(renderer, camX, camY, camW, camH);
  }

  for (auto &npc : NPCs) {
    npc->render(renderer, camX, camY, camW, camH);
  }
}