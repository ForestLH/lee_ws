#pragma once

#include "buffer.h"
#include "looper.h"
#include "socket.h"

namespace lee_ws {
class Poller;
class Looper;

class Connection {
 public:
  explicit Connection(std::unique_ptr<Socket> socket);
  ~Connection() = default;

  NON_COPYABLE(Connection);
  void SetCallBack(const std::function<void(Connection *)> &callback);
  auto GetCallBack() -> std::function<void()>;
  void SetEvents(event_t events);
  void SetRevents(event_t revents);
  void SetLooper(Looper *looper);
  auto GetSocket() -> Socket * { return socket_.get(); };
  auto GetFd() -> fd_t;
 private:
  Looper *owner_looper_{nullptr};
  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Buffer> read_buffer_;
  std::unique_ptr<Buffer> write_buffer_;
  event_t events_{};
  event_t revents_{};
  std::function<void()> callback_{nullptr};
};
} // namespace lee_ws

