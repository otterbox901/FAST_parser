#ifndef FAST_DECODER_H
#define FAST_DECODER_H

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string>
#include <memory>
#include "xml_parsing_coms/Node.h"
#include "Bit-processing-comms/decode_tree.h"

class FastDecoder {
public:
  explicit FastDecoder(std::unordered_map<std::string, std::unique_ptr<NODE>> templates);
  void load_reference_data(const std::unordered_map<uint64_t, std::string>& ref_data);
  void process_packet(const std::vector<uint8_t>& buffer, ssize_t bytes_received);
private:
  StateDictionary state_;
  std::unordered_map<std::string, std::unique_ptr<NODE>> templates_;
  std::unordered_map<uint64_t, std::string> reference_data_;
};
#endif // FAST_DECODER_H

