#pragma once

#include <unordered_map>
#include <memory>
#include <mutex>
#include "acceptor.h"
#include "config.h"
#include "connection.h"
#include "poller.h"
namespace lee_ws {
class Connection;

class Looper{
  
 public:
  Looper();

  void Loop();

  void AddAcceptor(Connection *acceptor_conn);

  void AddConnection(std::unique_ptr<Connection> connection);

  auto DeleteConnection() -> bool;
 private:
  std::unique_ptr<Poller> poller_;
  std::mutex latch_;
  bool exit_{false};
  std::unordered_map<fd_t, std::unique_ptr<Connection>> conns_map_;  // 主要是为了方便管理，比如要删除某个连接
};
}


