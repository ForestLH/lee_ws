#include "core/socket.h"
#include "fcntl.h"
#include "sys/socket.h"
#include <unistd.h>
#include <cassert>

namespace lee_ws {

Socket::Socket() noexcept : fd_{INVALID_FD} {}

Socket::Socket(fd_t fd) noexcept : fd_{fd} {}

Socket::Socket(Socket &&other) noexcept {
  fd_ = other.fd_;
  other.fd_ = INVALID_FD;
}

Socket &Socket::operator=(Socket &&other) noexcept {
  if (fd_ != INVALID_FD) {
    close(fd_);
  }
  std::swap(fd_, other.fd_);
  return *this;
}

Socket::~Socket() {
  if (fd_ != INVALID_FD) {
    close(fd_);
    fd_ = INVALID_FD;
  }
}

auto Socket::GetFd() const noexcept -> fd_t { return fd_; }

void Socket::Connect(NetAddress &server_address) {
  if (fd_ != INVALID_FD) {
    CreateByProtocol(server_address.GetProtocol());
  }
  if (connect(fd_, server_address.YieldAddr(), *server_address.YieldAddrLen()) == INVALID_FD) {
    throw std::logic_error("Socket: Connection() error");
  }
}

void Socket::Bind(NetAddress &server_address, bool set_reusable) {
  if (fd_ == INVALID_FD) {
    CreateByProtocol(server_address.GetProtocol());
  }
  if (set_reusable) {
    SetReusable();
  }
  if (bind(fd_, server_address.YieldAddr(), *server_address.YieldAddrLen()) == -1) {
    throw std::logic_error("Socket: Bind() error");
  }
}
void Socket::Listen() {
  assert(fd_ != INVALID_FD && "cannot Listen() with an invalid fd");
  listen(fd_, BACK_LOG);
}
auto Socket::Accept() -> fd_t { return 0; }
}

