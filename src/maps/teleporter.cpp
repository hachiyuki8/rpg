#include "teleporter.h"

int Teleporter::nextID = 0;

Teleporter::Teleporter(Map *src, Map *dest, int src_r, int src_c, int dest_r,
                       int dest_c) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating teleporter " << ID << std::endl;
  }

  src_map = src;
  dest_map = dest;
  src_row = src_r;
  src_col = src_c;
  dest_row = dest_r;
  dest_col = dest_c;
}

Teleporter::~Teleporter() {
  if (DEBUG) {
    std::cout << "Destroying teleporter " << ID << std::endl;
  }
}

void Teleporter::print() {
  std::cout << "Teleporter " << ID << std::endl;
  std::cout << "-From (" << src_row << ", " << src_col << ") to (" << dest_row
            << ", " << dest_col << ")" << std::endl;
}