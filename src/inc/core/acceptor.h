#pragma once
#include <iostream>
#include <vector>
#include "connection.h"
#include "looper.h"
#include "net_address.h"

namespace lee_ws {

class Acceptor {
 public:
  explicit Acceptor(Looper *listener, std::vector<Looper *> reactors, NetAddress server_address);
  ~Acceptor() = default;
  Acceptor(const Acceptor &acceptor) = delete;

  void BaseAcceptCallback(Connection *server_conn);


 private:
  std::vector<Looper *> reactors_;
  std::unique_ptr<Connection> acceptor_conn_;
  std::function<void (Connection *)> accept_callback_{};
  std::function<void (Connection *)> handler_callback_{};
};
} // namespace lee_ws

