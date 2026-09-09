//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_DECODE_DECIMAL_H
#define EXCHANGEPARSER_DECODE_DECIMAL_H
#include <cmath>

#endif // EXCHANGEPARSER_DECODE_DECIMAL_H
#include "decode_int.h"
#include <optional>

/// output value = matissa * 10**exponent
///
inline std::optional<double> decode_decimal(const std::vector<uint8_t>& buffer,
                                    size_t& index, bool is_optional)
{
  std::optional<int64_t> exponent= decode_int(buffer, index, is_optional);
  if (!exponent.has_value()) {
    return std::nullopt;
  }
  std::optional<int64_t> matissa= decode_int(buffer, index, false);
  return matissa.value()*std::pow(10,exponent.value()); // value compresses the 64int
}
