#include "core/net_address.h"
#include <sys/_endian.h>
#include <algorithm>
#include <cstring>
#include <exception>
#include "core/config.h"
#include <iostream>
#include <string>


namespace lee_ws {

NetAddress::NetAddress() noexcept {
  protocol_ = Protocol::Ipv4;
  SetAddress(DEFAULT_ADDR.data(), DEFAULT_PORT, protocol_);
}

NetAddress::NetAddress(const std::string &address, Protocol protocol) : protocol_(protocol) {
  auto colon = std::find(address.begin(), address.end(), ':');
  auto ip_address = std::string{DEFAULT_ADDR};
  auto port = DEFAULT_PORT;
  if (colon == address.end()) {
    ip_address = address;
  } else if (colon == address.begin()) {
    auto port_string = std::string{colon + 1, address.end()};
    port = std::stoi(port_string);
  } else {
    ip_address = std::string{address.begin(), colon};
    auto port_string = std::string{colon + 1, address.end()};
    port  = std::stoi(port_string);
  }
  SetAddress(ip_address.c_str(), port, protocol_);
}

auto NetAddress::GetProtocol() const noexcept -> Protocol { return protocol_; }

auto NetAddress::GetIp() const noexcept -> std::string {
  char ip_address[INET6_ADDRSTRLEN];  // long enough for both Ipv4 and Ipv6
  if (protocol_ == Protocol::Ipv4) {
    auto addr_ipv4 = reinterpret_cast<struct sockaddr_in *>(&addr_);
    inet_ntop(AF_INET, &addr_ipv4->sin_addr, ip_address, INET_ADDRSTRLEN);
  } else {
    auto addr_ipv6 = reinterpret_cast<struct sockaddr_in6 *>(&addr_);
    inet_ntop(AF_INET6, &addr_ipv6->sin6_addr, ip_address, INET6_ADDRSTRLEN);
  }
  return ip_address;
}

auto NetAddress::GetPort() const noexcept -> uint16_t {
  uint16_t port;
  if (protocol_ == Protocol::Ipv4) {
    auto addr_ipv4 = reinterpret_cast<struct sockaddr_in *>(&addr_);
    port = ntohs(addr_ipv4->sin_port);
  } else {
    auto addr_ipv6 = reinterpret_cast<struct sockaddr_in6 *>(&addr_);
    port = ntohs(addr_ipv6->sin6_port);
  }
  return port;
}
auto NetAddress::YieldAddr() -> struct sockaddr * { return &addr_; }

auto NetAddress::YieldAddrLen() -> socklen_t * { return &addr_len_; }

auto NetAddress::ToString() const noexcept -> std::string {
  return GetIp() + std::string("@") + std::to_string(GetPort());
}

auto operator<<(std::ostream &os, const NetAddress &address) -> std::ostream & {
  os << address.ToString();
  return os;
}

void NetAddress::SetAddress(const char *address, const int &port, const Protocol &protocol) {
  memset(&addr_, 0, sizeof(addr_));

  if (protocol == Protocol::Ipv4) {
    addr_len_ = sizeof(addr_);
    auto addr_ipv4 = reinterpret_cast<struct sockaddr_in *>(&addr_);
    addr_ipv4->sin_family = AF_INET;
    inet_pton(AF_INET, address, &addr_ipv4->sin_addr.s_addr);
    addr_ipv4->sin_port = htons(port);
  } else {
    auto addr_ipv6 = reinterpret_cast<struct sockaddr_in6 *>(&addr_);
    addr_ipv6->sin6_family = AF_INET6;
    inet_pton(AF_INET6, address, &addr_ipv6->sin6_addr.s6_addr);
    addr_ipv6->sin6_port = htons(port);
  }
}
} // namespace lee_ws
