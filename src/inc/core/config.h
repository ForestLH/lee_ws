#pragma once

#include <string>
#include <string_view>

namespace lee_ws {


constexpr static int DEFAULT_PORT = 80;
constexpr static std::string_view DEFAULT_ADDR{"127.0.0.1"};

static constexpr int INVALID_FD  = -1;
static constexpr int BACK_LOG = 128;
static constexpr uint32_t MIN_NUM_THREADS_IN_POOL = 2;

using fd_t = int32_t;
} // namespace lee_ws


