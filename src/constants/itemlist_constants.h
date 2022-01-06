#pragma once
#include "constants.h"

const int ITEMLIST_WIDTH = 960;
const int ITEMLIST_HEIGHT = 540;
const int ITEMLIST_GRID_SIZE = 60;
const int ITEMLIST_OBJECT_SIZE = 40;
const int ITEM_LIMIT = (ITEMLIST_WIDTH / ITEMLIST_GRID_SIZE) *
                       (ITEMLIST_HEIGHT / ITEMLIST_GRID_SIZE);
const int PER_ITEM_LIMIT = 99;