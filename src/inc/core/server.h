#pragma once
#include <vector>
#include "acceptor.h"
#include "looper.h"
#include "net_address.h"
#include "thread_pool.h"

namespace lee_ws {

class Server {
 public:
  explicit Server(NetAddress server_address, int concurrency = std::thread::hardware_concurrency() - 1);
  auto OnHandler() -> Server & {
//    acceptor_->
    return *this;
  }

 private:
  bool on_handle_set_{false};
  std::unique_ptr<Acceptor> acceptor_;
  std::vector<std::unique_ptr<Looper>> reactors_;
  std::unique_ptr<ThreadPool> pool_;
  std::unique_ptr<Looper> listener_;
};

} // namespace lee_ws