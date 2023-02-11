#include "core/acceptor.h"
#include "core/net_address.h"
#include "core/utils.h"


auto main() -> int {
  auto net_address = lee_ws::NetAddress("192.168.0.10:-xx");

  std::cout << "begin" << std::endl;
  lee_ws::DEFER([&](){std::cout << net_address << std::endl;});
  std::cout << "end" << std::endl;
  return 0;
}