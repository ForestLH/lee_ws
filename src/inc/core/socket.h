#pragma once

#include "config.h"
#include "net_address.h"
#include "utils.h"
namespace lee_ws {
class Socket {
 public:
  Socket() noexcept;

  explicit Socket(fd_t fd) noexcept;

  NON_COPYABLE(Socket);

  Socket(Socket &&other) noexcept;

  Socket &operator=(Socket &&other) noexcept;

  ~Socket();

  auto GetFd() const noexcept -> fd_t;

  void Connect(NetAddress &server_address);

  void Bind(NetAddress &server_address, bool set_reusable = true);

  void Listen();

  auto Accept() -> fd_t;

  void SetReusable();

  void SetNonBlocking();

  auto GetAttrs() -> int;

 private:

  void CreateByProtocol(Protocol protocol);

  fd_t fd_{INVALID_FD};
};
}