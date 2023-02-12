#pragma once
#include <future>
#include <iostream>
#include <queue>
#include "thread"
#include "utils.h"

namespace lee_ws {
class ThreadPool {
 public:
  explicit ThreadPool(uint32_t size = std::thread::hardware_concurrency() - 1);

  ~ThreadPool();

  NON_COPYABLE(ThreadPool);

  void Exit();

  auto GetSize() -> size_t;

  template <typename F, typename... Args>
  auto SubmitTask(F &&new_task, Args &&...args) -> decltype(auto);

  private:
  std::vector<std::thread> threads_;
  std::queue<std::function<void()>> tasks_;
  std::mutex latch_;
  std::condition_variable cv_;
  std::atomic<bool> exit_{false};
};

template <typename F, typename... Args>
auto ThreadPool::SubmitTask(F &&new_task, Args &&...args) -> decltype(auto)  {
  using return_type = std::invoke_result_t<F, Args...>; // 得到任务的返回值类型
  if (exit_) {
    throw std::runtime_error("Thread pool SubmitTask called while exited");
  }
  auto packaged_new_task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<F>(new_task), std::forward<Args>(args)...)
  );
  auto fut = packaged_new_task->get_future();
  {
    std::unique_lock<std::mutex> ul(latch_);
    tasks_.emplace([packaged_new_task]() { (*packaged_new_task)(); });
  }
  cv_.notify_one();
  return fut;
}
} // namespace lee_ws
