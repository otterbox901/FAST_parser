//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_DECODE_UINT_H
#define EXCHANGEPARSER_DECODE_UINT_H
#include <cstdint>
#include <optional>

#endif // EXCHANGEPARSER_DECODE_UINT_H


inline std::optional<uint64_t> decode_uint(const std::vector<uint8_t>& buffer,
                                    size_t& index, const bool is_optinal)
{
  uint64_t value= 0;
  while (true) {
    uint8_t curr_byte= buffer[index++];
    value= (value<<7)|(curr_byte & 0x7F);
    if (curr_byte & 0x80) break;

  }
  if (is_optinal) {
    if (value==0) {
      return std::nullopt;
    }
    value--;
  }
  return value;
}

/// in the main function the bool is passed as child->optional