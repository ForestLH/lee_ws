#pragma once
#include "connection.h"
#include <vector>
namespace lee_ws {

class Poller {
class Connection;
 public:
  auto Poll(int timeout) -> std::vector<Connection *>;
  void AddConnection(Connection *connection);

 private:


};


}  // namespace lee_ws