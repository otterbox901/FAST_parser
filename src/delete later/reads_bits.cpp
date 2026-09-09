
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct NODE;
class FastDecoder {
  private:
  const std::unordered_map<std::string, std::unique_ptr<NODE>>& registry;
  public:
  FastDecoder(const std::unordered_map<std::string, std::unique_ptr<NODE>>& template_registry);
  void packets(const std::vector<uint8_t>& buffer, ssize_t bytes_received);
};




