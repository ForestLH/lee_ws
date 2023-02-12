#include "core/thread_pool.h"
#include "gtest/gtest.h"



namespace lee_ws {

template <typename T>
void Print(std::initializer_list<T> list) {
  for (const auto &it : list) {
    std::cout << it << std::endl;
  }
}

template <typename T>
auto PrintSingle(T single) -> decltype(auto) {
  std::cout << single << std::endl;
  return single;
}



auto Print(int number) -> int {
  std::cout << number << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(4));

  return number + 10;
}

TEST(THREAD_POOL, BASIC_TEST) {
  auto pool = ThreadPool{};

//  pool.SubmitTask([&](){std::cout << 12 << std::endl;});
//  pool.SubmitTask<void(std::initializer_list<int>), std::initializer_list<int>>(Print<int>, {12, 32, 54});
//  Print<int>({211, 12, 32});
//  PrintSingle(12);
  auto ret = pool.SubmitTask<int(int), int>(Print, 12);
//  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "main" << std::endl;
  std::cout << "In main:" << ret.get() << "ddd"<< std::endl;  // get是个阻塞的过程, 并且不允许两次调用get
}


} // namespace lee_ws