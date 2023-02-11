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
void PrintSingle(T single) {
  std::cout << single << std::endl;
}



//void Print(int number) {
//  std::cout << number << std::endl;
//}

TEST(THREAD_POOL, BASIC_TEST) {
  auto pool = ThreadPool{};

//  pool.SubmitTask([&](){std::cout << 12 << std::endl;});
  pool.SubmitTask<void(std::initializer_list<int>), std::initializer_list<int>>(Print<int>, {12, 32, 54});
//  Print<int>({211, 12, 32});
//  PrintSingle(12);
//  pool.SubmitTask<void(int), int>(PrintSingle, 12);
}


} // namespace lee_ws