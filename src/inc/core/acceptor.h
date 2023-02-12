#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "connection.h"
#include "looper.h"
#include "net_address.h"

namespace lee_ws {
class Connection;
class Looper;
/**
 * @brief Acceptor负责处理新的连接，并且将连接分配给其他的looper来处理
 */
class Acceptor {
 public:
  explicit Acceptor(Looper *listener, std::vector<Looper *> reactors, NetAddress server_address);
  ~Acceptor() = default;
  NON_COPYABLE(Acceptor);

  void BaseAcceptCallback(Connection *server_conn);

  void SetCustomAcceptCallback(std::function<void(Connection *)> custom_callback);

  void SetCustomHandlerCallback(std::function<void(Connection *)> custom_callback);

 private:
  std::vector<Looper *> reactors_;
  std::unique_ptr<Connection> acceptor_conn_;
  std::function<void (Connection *)> accept_callback_{};
  std::function<void (Connection *)> handler_callback_{};
};
} // namespace lee_ws

