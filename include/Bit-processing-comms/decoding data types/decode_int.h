//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_DECODE_INT_H
#define EXCHANGEPARSER_DECODE_INT_H
#include <cstdint>
#include <optional>
#include <vector>

#endif // EXCHANGEPARSER_DECODE_INT_H

inline std::optional<int64_t> decode_int(const std::vector<uint8_t>& buffer,
                                  size_t& index, const bool is_optional)
{
  int64_t value= 0;
  if (buffer[index]&0x40) {
    value--;
  }
  while (true) {
    const uint8_t next_byte = buffer[index++];
    value= (value<<7)|(next_byte&0x7F);
    if (next_byte&0x80) break;
  }
  if (is_optional) {
    if (value==0) {
      return std::nullopt;
    }
    if (value>0) {
      value--;
    }
  }
  return value;
};

