#pragma once
#include "constants.h"

enum class ObjectProperty { CAN_COLLIDE, CAN_PICKUP, CAN_INTERACT, CAN_USE };
enum class ObjectType {
  DIVIDER,  // render as transparent if not in DEBUG mode
  MONEY,    // upon pickup, increase player money instead of going to inventory
  QUEST_OBJECT,  // cannot be sold
  OTHERS
};
const int OBJECT_SIZE = 25;
const std::string OBJECT_DIVIDER = "30_divider.png";