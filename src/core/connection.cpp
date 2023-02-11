#include "core/connection.h"

namespace lee_ws {



Connection::Connection(std::unique_ptr<Socket> socket) {

}

void Connection::SetCallBack(const std::function<void(Connection *)> &callback) {
  callback_ = [callback, this] { return callback(this); };
}
auto Connection::GetCallBack() -> std::function<void()> { return callback_; }
}