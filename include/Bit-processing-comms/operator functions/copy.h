#ifndef EXCHANGEPARSER_COPY_H
#define EXCHANGEPARSER_COPY_H
#include "xml_parsing_coms/Node.h"
#include <optional>

#endif // EXCHANGEPARSER_COPY_H

inline std::optional<FastValue> copy_opp(const NODE* child, StateDictionary& state)
{
  if (const auto it = state.find(child->name); it != state.end()) return it->second;
  return child->initial_value;
}
