#pragma once
#include <cstddef>
#include <cstdint>

namespace Arbor {
using FrameID = uint32_t;
using PageID = uint64_t;

constexpr FrameID INVALID_FRAME_ID = UINT32_MAX;
constexpr PageID INVALID_PAGE_ID = UINT64_MAX;
constexpr size_t PAGE_SIZE = 4096;
}  // namespace Arbor
