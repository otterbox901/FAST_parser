//
// Created by alex on 2026-08-20.
//

#ifndef EXCHANGEPARSER_INCREMENT_H
#define EXCHANGEPARSER_INCREMENT_H
#include <cstdint>
#include <optional>
#include <variant>
#endif // EXCHANGEPARSER_INCREMENT_H

inline std::optional<FastValue> increment(const NODE* child, StateDictionary& state)
{
  auto it= state.find(child->name);
  if (it != state.end()) {
    if (auto* prev_val = std::get_if<uint64_t>(&it->second)) {
      uint64_t new_val = *prev_val+1;
      state[child->name] = new_val;
      return new_val;
    }
  }
  return child->initial_value;
}