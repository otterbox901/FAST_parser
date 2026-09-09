#ifndef EXCHANGEPARSER_DECODE_TREE_H
#define EXCHANGEPARSER_DECODE_TREE_H
#include "decoding data types/decode_byte_vector.h"
#include "decoding data types/decode_decimal.h"
#include "decoding data types/decode_int.h"
#include "decoding data types/decode_string.h"
#include "decoding data types/decode_uint.h"
#include "operator output.h"

#include "xml_parsing_coms/Node.h"
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "FastValue+StateDic.h"


//// when you run the decode int function it allcoates
/// 64 bits regardless of what the type is --> big memory usage >:(

inline std::string fastvalue_to_string(const FastValue& value) {
  return std::visit([]<typename T0>(T0&& arg) -> std::string {
    using T= std::decay_t<T0>;
    if constexpr (std::is_same_v<T, std::string>) return arg;
    else if constexpr (std::is_same_v<T, std::vector<uint8_t>>) {
      return "[ByteVector - Size: ]"+ std::to_string(arg.size())+"]";
    }
    else return std::to_string(arg);
  }, value);
}
//// above is helper to output text readable sting remove later

inline void decode_tree(const NODE* node, const std::vector<uint8_t>&buffer,
size_t& index, const uint64_t pmap, uint64_t pmap_bit_index, StateDictionary& state) {
  if (!node) return;

  for (const auto& child: node->children) {
    bool present= true;
    if (child->pmap) {
      present = (pmap>>pmap_bit_index) & 1;

      pmap_bit_index--;
    }

    if (child->type =="sequence") {
      uint64_t length=0;
      if (present) {
        length= decode_uint(buffer, index, child->optional).value();
      }
      for (uint64_t i=0; i<length; i++) {
        const uint64_t seq_map = decode_uint(buffer, index, child->optional).value();
        constexpr int seq_pmap_bit_index= 6;
        decode_tree(child.get(), buffer, index, seq_map, seq_pmap_bit_index,state);
      }
    }
    else if (child -> type == "group") {
      const uint64_t group_pmap= decode_uint(buffer, index, child->optional).value();
      constexpr int group_pmap_bit_index= 6;
      decode_tree(child.get(), buffer, index, group_pmap, group_pmap_bit_index, state);
    }
    else if (present) {
      if (child->type == "uInt32" || child->type == "uInt64" || child->type == "length") {
        if (std::optional<uint64_t> val =
                decode_uint(buffer, index, child->optional);
            val.has_value()) {
          state[child->name]= val.value();
        }
      }
      else if (child->type == "int32" || child->type == "int64") {
        if (std::optional<int64_t> val =
                decode_int(buffer, index, child->optional);
            val.has_value()) {
          state[child->name]= val.value();
        }
      }
      else if (child->type == "string") {
        if (std::optional<std::string> val =
                decode_string(buffer, index, child->optional);
            val.has_value()) {
          state[child->name]= val.value();
        }
      }
      else if (child->type == "decimal") {
        if (std::optional<double> val =
                decode_decimal(buffer, index, child->optional);
            val.has_value()) {
          state[child->name]= val.value();
        }
      }
      else if (child->type == "byteVector" || child->type == "unicode") {
        if (std::optional<std::vector<uint8_t>> val =
                decode_byte_vector(buffer, index, child->optional);
            val.has_value()) {
          state[child->name]= val.value();
        }
      }
      else {
        std::cerr << "Unknown FAST data type: " << child->type << "\n";
      }
    }
    else {
      if (std::optional<FastValue> derived_value =
              opp_output(child.get(), state, buffer, index, present);
          derived_value.has_value()) {
        state[child->name]= derived_value.value();
        // here it outputs into json or text
        std::cout << "Field: " << child->name
        << ", Value "<< fastvalue_to_string(derived_value.value()) << "\n";
      }
    }
  }
}
#endif // EXCHANGEPARSER_DECODE_TREE_H

