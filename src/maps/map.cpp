#include "map.h"

#include "../entities/character.h"

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
        Tile t(AssetManager::tileTextures[TILES[index]], col * tileSize,
               row * tileSize, tileSize, TileState::REACHABLE);
        vec.push_back(t);
      } else {
        Tile t(AssetManager::tileTextures[TILES[-index]], col * tileSize,
               row * tileSize, tileSize, TileState::UNREACHABLE);
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

void Map::addTeleporter(Teleporter tp) {
  if (tp.src_map != this && tp.dest_map != this) {
    std::cout << "Invalid teleporter to be added to map " << ID << std::endl;
    return;
  }
  teleporters.push_back(tp);
}

void Map::addObject(ObjectWrapper ow) { objectWrappers.push_back(ow); }

void Map::removeObject(ObjectWrapper ow) {
  objectWrappers.erase(
      std::remove(objectWrappers.begin(), objectWrappers.end(), ow),
      objectWrappers.end());
}

void Map::addNPC(CharacterNPC *npc) { NPCs.push_back(npc); }

void Map::addEnemy(Enemy *e) { enemies.push_back(e); }

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

  for (auto &e : enemies) {
    if (e->isInvalidPosition(x, y, w, h)) {
      return true;
    }
  }

  for (auto &ow : objectWrappers) {
    if (ow.isInvalidPosition(x, y, w, h)) {
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

bool Map::isInvalidEnemyPosition(Enemy *e) {
  if (e->xPos < 0 || e->xPos + e->width > width || e->yPos < 0 ||
      e->yPos + e->height > height) {
    return true;
  }

  for (auto &ts : tiles) {
    for (auto &t : ts) {
      if (t.isInvalidPosition(e->xPos, e->yPos, e->width, e->height)) {
        return true;
      }
    }
  }

  for (auto &oe : enemies) {
    if (e != oe &&
        oe->isInvalidPosition(e->xPos, e->yPos, e->width, e->height)) {
      return true;
    }
  }

  for (auto &ow : objectWrappers) {
    if (ow.isInvalidPosition(e->xPos, e->yPos, e->width, e->height)) {
      return true;
    }
  }

  for (auto &npc : NPCs) {
    if (npc->isInvalidPosition(e->xPos, e->yPos, e->width, e->height)) {
      return true;
    }
  }

  if (AssetManager::player->isInvalidPosition(e->xPos, e->yPos, e->width,
                                              e->height)) {
    return true;
  }

  return false;
}

std::tuple<Map *, float, float> Map::onInteract(Character *curPlayer, float x,
                                                float y, float w, float h) {
  for (auto &npc : NPCs) {
    if (npc->onInteract(curPlayer, x, y, w, h)) {
      return std::make_tuple(this, x, y);
    }
  }

  for (auto &tp : teleporters) {
    if (tp.src_map == this) {
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

  for (auto &ow : objectWrappers) {
    if (ow.onInteract(x, y, w, h)) {
      return std::make_tuple(this, x, y);
    }
  }

  return std::make_tuple(this, x, y);
}

std::tuple<int, Enemy *> Map::onAttack(int attack, float x, float y, float w,
                                       float h) {
  Enemy *np = NULL;
  for (auto &e : enemies) {
    if (e->isInRange(x, y, w, h)) {
      std::pair<int, int> res = e->onAttack(x, attack);
      if (res.first == -1 && res.second == -1) {
        return std::make_tuple(-1, np);  // still in last attack animation
      }
      if (!res.second) {
        return std::make_tuple(res.first, e);  // enemy killed
      } else {
        return std::make_tuple(res.first, np);
      }
    }
  }

  return std::make_tuple(-1, np);
}

void Map::render(SDL_Renderer *renderer, float camX, float camY, float camW,
                 float camH) {
  for (auto &ts : tiles) {
    for (auto &t : ts) {
      t.render(renderer, camX, camY, camW, camH);
    }
  }

  for (auto &e : enemies) {
    e->render(this, renderer, camX, camY, camW, camH);
  }

  for (auto &ow : objectWrappers) {
    ow.render(renderer, camX, camY, camW, camH);
  }

  for (auto &npc : NPCs) {
    npc->render(renderer, camX, camY, camW, camH);
  }
}