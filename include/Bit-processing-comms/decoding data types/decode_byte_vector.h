//
// Created by alex on 2026-08-20.
//

#ifndef EXCHANGEPARSER_BYTEVEC_UNICODE_H
#define EXCHANGEPARSER_BYTEVEC_UNICODE_H
#include <cstdint>
#include <optional>
#include <vector>
#include "decode_uint.h"

#endif // EXCHANGEPARSER_BYTEVEC_UNICODE_H

inline std::optional<std::vector<uint8_t>> decode_byte_vector(const std::vector<uint8_t>& buffer,
                                                              size_t& index, bool is_optional)
{
  std::optional<uint32_t> length = decode_uint(buffer, index, is_optional);

  if (!length.has_value()) {
    return std::nullopt;
  }

  std::vector<uint8_t> payload;
  uint32_t byte_count = length.value();
  payload.reserve(byte_count);

  for (uint32_t i = 0; i < byte_count; ++i) {
    payload.push_back(buffer[index++]);
  }

  return payload;
}
