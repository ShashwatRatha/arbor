#include "disk-manager.h"

#include <fcntl.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <stdexcept>

#include "types.h"

DiskManager::DiskManager(const char *path)
    : mFD(open(path, O_RDWR | O_CREAT, 0666)), mOwnsFd(true), mNumPages(0) {
  if (mFD < 0) throw std::runtime_error("Failed to open file");
  auto size = lseek(mFD, 0, SEEK_END);
  if (size < 0) throw std::runtime_error("Failed to stat file");
  mNumPages = static_cast<PageID>(size / PAGE_SIZE);
}

DiskManager::DiskManager(int32_t fd, bool t)
    : mFD(fd), mOwnsFd(t), mNumPages(0) {
  if (mFD < 0) throw std::runtime_error("Failed to open file");
  auto size = lseek(mFD, 0, SEEK_END);
  if (size < 0) throw std::runtime_error("Failed to stat file");
  mNumPages = static_cast<PageID>(size / PAGE_SIZE);
}

DiskManager::~DiskManager() {
  if (mOwnsFd && mFD >= 0) close(mFD), mFD = -1;
}

PageID DiskManager::allocatePage() { return mNumPages++; }

bool DiskManager::writePage(PageID id, const uint8_t *outBuf) {
  if (mFD < 0) throw std::runtime_error("File not open");

  off_t offset = id * PAGE_SIZE;
  return pwrite(mFD, static_cast<const void *>(outBuf), PAGE_SIZE, offset) !=
         -1;
}

bool DiskManager::readPage(PageID id, uint8_t *inBuf) {
  if (mFD < 0) throw std::runtime_error("File not open");

  off_t offset = id * PAGE_SIZE;
  return pread(mFD, static_cast<void *>(inBuf), PAGE_SIZE, offset) > 0;
}
