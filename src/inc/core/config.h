#pragma once

#include <string>
#include <string_view>
#include <sys/epoll.h>
namespace lee_ws {


constexpr static int DEFAULT_PORT = 80;
constexpr static std::string_view DEFAULT_ADDR{"127.0.0.1"};

static constexpr int INVALID_FD  = -1;
static constexpr int BACK_LOG = 128;
static constexpr uint32_t MIN_NUM_THREADS_IN_POOL = 2;

static constexpr unsigned POLL_ADD = EPOLL_CTL_ADD;
static constexpr unsigned POLL_READ = EPOLLIN;
static constexpr unsigned POLL_ET = EPOLLET;
static constexpr int TIMEOUT = 3000;


using fd_t = int32_t;
using event_t = uint32_t;
} // namespace lee_ws


