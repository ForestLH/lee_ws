#include "core/thread_pool.h"
#include <future>
#include "core/config.h"

namespace lee_ws {

ThreadPool::ThreadPool(uint32_t size) {
  size = std::max({size, MIN_NUM_THREADS_IN_POOL});
  for (auto i = 0; i < size; i++) {
    threads_.emplace_back([this](){
      while (true) {
        std::function<void()> next_task;
        {
          std::unique_lock<std::mutex> lock(latch_);
          cv_.wait(lock, [this](){
            return exit_ || !tasks_.empty();
          });
          if (exit_ && tasks_.empty()) {
            return;
          }
          next_task = tasks_.front();
          tasks_.pop();
        }
        next_task();
      }
    });
  }
}
ThreadPool::~ThreadPool() {
  Exit();
  for (auto &worker : threads_) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

void ThreadPool::Exit() {
  exit_ = true;
  cv_.notify_all();
}

auto ThreadPool::GetSize() -> size_t { return threads_.size(); }



} // namespace lee_ws