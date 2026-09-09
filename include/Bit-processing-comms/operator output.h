//
// Created by alex on 2026-08-20.
//

#ifndef EXCHANGEPARSER_ALL_DT_TOGETHER_H
#define EXCHANGEPARSER_ALL_DT_TOGETHER_H
#include "operator functions/copy.h"
#include "operator functions/delta.h"
#include "operator functions/increment.h"
#include "operator functions/tail.h"
#include <optional>



inline std::optional<FastValue>opp_output(const NODE* child, StateDictionary& state,
                                          const std::vector<uint8_t>& buffer,
                                          size_t& index, const bool present)
{
  const std::string opp = child->opp;
  if (opp == "none") {
    std::optional<uint32_t>val = decode_uint(buffer, index, child->optional);
    return val;
  }
  if (opp == "copy") {
    return copy_opp(child,state);
  }
  if (opp == "constant") {
    if (!child->optional) return child->initial_value;
     {
      if (present) return child->initial_value;
      return std::nullopt;
    }
  }
  if (opp == "delta") {
    return delta(child, state, buffer, index);
  }
  if (opp == "default") {
    if (present) {
      std::optional<uint32_t> val = decode_uint(buffer, index, child->optional);
      return val;
    }
    return child->initial_value;

  }
  if (opp == "tail") {
    return tail(child, state, buffer, index, present);
  }
  if (opp == "increment") {
    return increment(child, state);
  }
  return std::nullopt;
}

#endif // EXCHANGEPARSER_ALL_DT_TOGETHER_H