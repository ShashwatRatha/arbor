#pragma once

#include <cstdint>

#include "types.h"

using namespace Arbor;

class DiskManager {
 public:
  DiskManager(const char *path);
  DiskManager(int32_t fd, bool takeOwnership = false);
  ~DiskManager();

  DiskManager(const DiskManager &) = delete;
  DiskManager(DiskManager &&) = delete;
  DiskManager &operator=(const DiskManager &) = delete;
  DiskManager &operator=(DiskManager &&) = delete;

  PageID allocatePage();
  bool readPage(PageID id, uint8_t *inBuf);
  bool writePage(PageID id, const uint8_t *outBuf);

 private:
  int32_t mFD;
  bool mOwnsFd;
  PageID mNumPages;
};
