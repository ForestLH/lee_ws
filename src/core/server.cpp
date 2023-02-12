#include "core/server.h"
#include "core/net_address.h"
#include <thread>

namespace lee_ws {

Server::Server(NetAddress server_address, int concurrency) : pool_(std::make_unique<ThreadPool>(concurrency)),
                                                             listener_(std::make_unique<Looper>()) {
  for (auto i = 0; i < pool_->GetSize(); i++) {
    reactors_.emplace_back(std::make_unique<Looper>());
  }
  for (auto &reactor : reactors_) {
    pool_->SubmitTask([cap = reactor.get()] {cap->Loop()});
  }
  std::vector<Looper *> raw_reactors;
  raw_reactors.reserve(reactors_.size());
  std::transform(reactors_.begin(), reactors_.end(), std::back_inserter(raw_reactors),
                 [](auto &uni_ptr) { return uni_ptr.get(); });
  acceptor_ = std::make_unique<Acceptor>(listener_.get(), raw_reactors, server_address);
}

}  // namespace lee_ws
