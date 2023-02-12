#include "core/looper.h"
#include <utility>


namespace lee_ws {

Looper::Looper() {

}

void Looper::Loop() {
  while (!exit_) {
    auto ready_conns = poller_->Poll(TIMEOUT);
    for (auto &conn : ready_conns) {
      // conn
    }
  }
}

void Looper::AddConnection(std::unique_ptr<Connection> connection) {
  std::unique_lock<std::mutex> ul(latch_);
  poller_->AddConnection(connection->get());
  auto fd = connection->GetFd();
  conns_map_.insert(fd, std::move(connection));
}

auto Looper::DeleteConnection() -> bool {
  return false;
}

}  // namespace lee_ws
