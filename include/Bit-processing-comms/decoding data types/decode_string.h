//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_DECODE_STRING_H
#define EXCHANGEPARSER_DECODE_STRING_H
#include <bits/locale_facets_nonio.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>



inline std::optional<std::string> decode_string(const std::vector<uint8_t>& buffer, std::size_t& index,
                                                const bool is_optional)
{
  if (is_optional && index<buffer.size() && buffer[index] == 0x80) {
    index++;
    return std::nullopt;
  }
  std::string value;

  while (index<buffer.size()) {
    uint8_t curr_byte= buffer[index++];
    value.push_back(static_cast<char>(curr_byte & 0x7f));
    if (curr_byte & 0x80) break;
  }
  return value;
}

#endif // EXCHANGEPARSER_DECODE_STRING_H