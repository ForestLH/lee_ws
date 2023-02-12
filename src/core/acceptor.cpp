#include "core/acceptor.h"
#include <random>

namespace lee_ws {

/**
 *
 * @param listener  其实我觉得这里应该给listener单独设计一个类比较好，而不是这样AddAcceptor去做，并且使用嵌入式的设计(has-a)而不是继承
 * @param reactors
 * @param server_address
 */
Acceptor::Acceptor(Looper *listener, std::vector<Looper *> reactors, NetAddress server_address)
    : reactors_(std::move(reactors)) {
  auto accept_sock = std::make_unique<Socket>();
  accept_sock->Bind(server_address, true);
  accept_sock->Listen();
  acceptor_conn_ = std::make_unique<Connection>(std::move(accept_sock));
  acceptor_conn_->SetEvents(POLL_READ);
  acceptor_conn_->SetLooper(listener);
  listener->AddAcceptor(acceptor_conn_.get());
//  BaseAcceptCallback();
  SetCustomAcceptCallback([](Connection *){});
  SetCustomHandlerCallback([](Connection *){});

}

void Acceptor::BaseAcceptCallback(Connection *server_conn) {
  NetAddress client_address;
  auto accept_fd = server_conn->GetSocket()->Accept();
  if (accept_fd == -1) {
    return;
  }
  auto client_sock = std::make_unique<Socket>(accept_fd);
  client_sock->SetNonBlocking();
  auto client_conn = std::make_unique<Connection>(std::move(client_sock));
  client_conn->SetEvents(POLL_READ | POLL_ET);
  client_conn->SetCallBack(handler_callback_);
  std::random_device rd;
  int idx = rd() % reactors_.size();  // NOLINT
  client_conn->SetLooper(reactors_[idx]);
  reactors_[idx]->AddConnection(std::move(client_conn));
  client_conn->SetLooper(reactors_[idx]);
}
void Acceptor::SetCustomAcceptCallback(std::function<void(Connection *)> custom_callback) {
  accept_callback_ = std::move(custom_callback);
  acceptor_conn_->SetCallBack([this](Connection *conn) {
    BaseAcceptCallback(conn);
  });
}
void Acceptor::SetCustomHandlerCallback(std::function<void(Connection *)> custom_callback) {
  handler_callback_ = std::move(custom_callback);
}

}  // namespace lee_ws