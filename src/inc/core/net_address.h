#pragma once
#include <arpa/inet.h>
#include <string>

namespace lee_ws {

enum class Protocol { Ipv4, Ipv6 };

class NetAddress {
 public:
  NetAddress() noexcept;
  explicit NetAddress(const std::string &address, Protocol protocol = Protocol::Ipv4);

  ~NetAddress() = default;
  auto GetProtocol() const noexcept -> Protocol;
  auto GetIp() const noexcept -> std::string;
  auto GetPort() const noexcept -> uint16_t;
  auto YieldAddr() -> struct sockaddr *;
  auto YieldAddrLen() -> socklen_t *;
  auto ToString() const noexcept -> std::string;

 private:
  void SetAddress(const char *address, const int &port, const Protocol &protocol);


  Protocol protocol_{Protocol::Ipv4};
  mutable struct sockaddr addr_{};
  socklen_t addr_len_{};
};

auto operator<<(std::ostream &os, const NetAddress &address) -> std::ostream &;

} // namespace lee_ws