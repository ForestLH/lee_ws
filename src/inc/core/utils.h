#pragma once

#include <utility>
#include <functional>

namespace lee_ws {

class DeferHelper
{
 public:
  explicit DeferHelper(std::function<void()> defer) : defer_(std::move(defer)) {}

  ~DeferHelper() {
    if (defer_) {
      defer_();
    }
  }
 private:
  const std::function<void()> defer_;
};

#define AA(B, C) B##C
#define BB(B, C) AA(B,C)
#define DEFER(callback) DeferHelper BB(defer_helper_, __LINE__)(callback)


#define NON_COPYABLE(class_name) \
  class_name(const class_name &) = delete; \
  class_name &operator=(const class_name &) = delete


}