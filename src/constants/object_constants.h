#pragma once
#include "constants.h"

enum class ObjectProperty { CAN_COLLIDE, CAN_PICKUP, CAN_INTERACT, CAN_USE };
enum class ObjectType {
  MONEY,
  QUEST_OBJECT,
  ADD_EXP,
  ADD_SKILL,
  ADD_STAT,
  OTHERS
};
const int OBJECT_SIZE = 25;