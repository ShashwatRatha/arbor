#pragma once

#include <cstdint>

#include "types.h"

using namespace Arbor;

struct Page {
  PageID pageID = INVALID_PAGE_ID;
  bool isDirty = false;
  uint32_t pinCount = 0;
  uint8_t buffer[PAGE_SIZE] = {};
};
