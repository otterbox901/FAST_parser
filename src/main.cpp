#include "xml_parsing_coms/Node.h"
#include "xml_parsing_coms/parser_func.h"
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "Bit-processing-comms/FastDecodeClass.h"
#include <sys/socket.h>


int main() {
  /// initialize the struct
  std::unordered_map<std::string, std::unique_ptr<NODE>> template_registry;

  /// populate the struct with the XML contents
  parser_func(template_registry, "!placeholder!");

  // Move the XML template into the FastDecode class
  // without allocating new memory
  FastDecoder decoder(std::move(template_registry));

  /// hold the incomming bytes from the udp socket
  std::vector<uint8_t>network_buffer(2048);
  int udp_socket= socket(AF_INET, SOCK_DGRAM, 0);
  while (true) {
    ssize_t bytes_received = recvfrom(
      udp_socket,
      network_buffer.data(),
      network_buffer.size(),
      nullptr,
      nullptr,
      0
    );
    if (bytes_received>0) {
      decoder.process_packet(network_buffer, bytes_received);
    }
  }
  return 0;
}

