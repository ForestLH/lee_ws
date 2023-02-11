#include "core/server.h"
#include "core/net_address.h"
#include <thread>

namespace lee_ws {

Server::Server(NetAddress server_address, int concurrency) : pool_(std::make_unique<ThreadPool>(concurrency)),
                                                             listener_(std::make_unique<Looper>()) {
  for (auto i = 0; i < pool_->GetSize(); i++) {
//        pool_->
  }
}
}
