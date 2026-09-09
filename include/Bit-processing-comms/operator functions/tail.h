#ifndef EXCHANGEPARSER_TAIL_H
#define EXCHANGEPARSER_TAIL_H
#include "xml_parsing_coms/Node.h"

#include <optional>
#include <string>

#endif // EXCHANGEPARSER_TAIL_H

inline std::optional<FastValue> tail(const NODE* child, StateDictionary& state,
                                    const std::vector<uint8_t>& buffer, size_t& index,
                                    const bool present)
{
  if (!present) return state[child->name];
  {
    const std::optional<std::string> tail_val = decode_string(buffer, index, child->optional);
    const auto prev_val = std::get<std::string>(state[child->name]);
    std::string new_val = prev_val+tail_val.value();
    return new_val;
  }
  return child->initial_value;
}