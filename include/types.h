#pragma once

#include <cstddef>
#include <cstdint>

namespace Arbor {
using PageID = uint64_t;
using FrameID = uint32_t;

constexpr size_t PAGE_SIZE = 4096;
constexpr PageID INVALID_PAGE_ID = UINT64_MAX;
constexpr FrameID INVALID_FRAME_ID = UINT32_MAX;
}  // namespace Arbor
