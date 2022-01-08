#include "teleporter.h"

int Teleporter::nextID = 0;

Teleporter::Teleporter(Map *src, Map *dest,
                       std::map<std::pair<int, int>, std::pair<int, int>> sd) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating teleporter " << ID << std::endl;
  }

  src_map = src;
  dest_map = dest;
  srcToDest = sd;
}

Teleporter::~Teleporter() {
  if (DEBUG) {
    std::cout << "Destroying teleporter " << ID << std::endl;
  }
}

void Teleporter::print() { std::cout << "Teleporter " << ID << std::endl; }