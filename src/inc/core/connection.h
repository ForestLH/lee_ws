#pragma once

#include "buffer.h"
#include "looper.h"
#include "socket.h"

namespace lee_ws {
class Connection {
 public:
  explicit Connection(std::unique_ptr<Socket> socket);
  ~Connection() = default;

  NON_COPYABLE(Connection);
  void SetCallBack(const std::function<void(Connection *)> &callback);
  auto GetCallBack() -> std::function<void()>;

 private:
  Looper *owner_looper_{nullptr};
  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Buffer> read_buffer_;
  std::unique_ptr<Buffer> write_buffer_;
  uint32_t events_{};
  uint32_t revents_{};
  std::function<void()> callback_{nullptr};
};
} // namespace lee_ws

