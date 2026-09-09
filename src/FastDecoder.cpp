# include "Bit-processing-comms/FastDecodeClass.h"
#include "Bit-processing-comms/decoding data types/decode_uint.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>
#include <optional>

FastDecoder::FastDecoder(std::unordered_map<std::string, std::unique_ptr<NODE>> templates)
  : templates_(std::move(templates)){}

void FastDecoder::load_reference_data(
    const std::unordered_map<uint64_t, std::string>& ref_data) {
  reference_data_ = ref_data;
}

void FastDecoder::process_packet(const std::vector<uint8_t>& buffer,
                                  ssize_t bytes_received)
{
  if (bytes_received <= 0) return;
  size_t index = 0;

  const std::optional<uint64_t> pmap = decode_uint(buffer, index, false);
  const std::optional template_id = decode_uint(buffer, index, false).value_or(0);

  if (!pmap.has_value() || !template_id.has_value()) {
    std::cerr << "malformed packet header.\n";
    return;
  }

  std::string id_str= std::to_string(template_id.value());

  auto it= templates_.find(id_str);
  if (it != templates_.end()) {
    const NODE* node = it->second.get();
    int pmap_bit_index = 6;
    decode_tree(node, buffer, index, pmap.value(), pmap_bit_index, state_);
  }
  else std::cerr<<"template_id "<< id_str << " not found"<<'\n';
}