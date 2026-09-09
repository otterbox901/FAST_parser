//
// Created by alex on 2026-08-20.
//

#ifndef EXCHANGEPARSER_DELTA_H
#define EXCHANGEPARSER_DELTA_H
#include <cstdint>
#include <variant>
#include <optional>

#endif // EXCHANGEPARSER_DELTA_H
inline std::optional<FastValue> delta(const NODE* child, StateDictionary& state,
                                const std::vector<uint8_t>& buffer, size_t& index)
{
  if (std::optional<int64_t> delta = decode_int(buffer, index, child->optional);
      delta.has_value()) {
    uint32_t value= 0;
    auto it= state.find(child->name);
    if (it != state.end()) {
      if (auto* prev= std::get_if<uint64_t>(&it->second)) {
        state[child->name]= *prev+delta.value();
        return state[child->name];
      }
    }
    return value;
  }
  return child->initial_value;
}

/// only for ints
