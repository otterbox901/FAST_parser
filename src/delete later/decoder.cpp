

#include <bits/locale_facets_nonio.h>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct NODE;
class FastDecoder;

uint32_t decode_uint(const std::vector<uint8_t>& buffer, size_t& index)
{
  uint32_t value= 0;
  while (true) {
    uint8_t curr_byte= buffer[index++];
    value= (value<<7)|(curr_byte & 0x7F);
    if (curr_byte & 0x80) break;

  }
  return value;
}

void decode_tree(const NODE* node, const std::vector<uint8_t>&buffer,
                              size_t& index, uint32_t pmap, uint32_t pmap_bit_index)
{
  if (!node) return;

  for (const auto& child: node->children) {
    bool present= true;
    if (child->pmap) {
      present = (pmap>>pmap_bit_index) & 1;

      pmap_bit_index--;
      if (pmap_bit_index<0) {
        ////
      }
    }

    if (child->type =="sequence") {
      uint32_t length=0;
      if (present) {
        length= decode_uint(buffer, index);
      }
      for (uint32_t i=0; i<length; i++) {
        uint32_t seq_map = decode_uint(buffer, index);
        int seq_pmap_bit_index= 6;
        decode_tree(child.get(), buffer, index, seq_map, seq_pmap_bit_index);
      }
    }
    else if (child -> type == "group") {
      uint32_t group_pmap= decode_uint(buffer, index);
      int group_pmap_bit_index= 6;
      decode_tree(child.get(), buffer, index, group_pmap, group_pmap_bit_index);
    }
    else if (present) {
      if (child->type == "uInt32" || child->type == "uInt64" || child->type == "length") {
        ...
        ...
        ...
      }
      else if (child -> type == "string") {
        ...
      }
      else if (child -> type == "decimal") {

      }
    }
    else {

    }
  }
}



void packets(const std::vector<uint8_t>& buffer, ssize_t bytes_received) {
  if (bytes_received<=0) return;
  size_t index= 0;

  uint32_t pmap= decode_uint(buffer, index);
  uint32_t template_id = decode_uint(buffer, index);
  std::string id_str= std::to_string(template_id);

  auto it = registry.find(id_str);
  if (it != registry.end()) {

    const NODE* node= it->second;
    int pmap_bit_index= 6
    decode_tree(node, index, pmap, pmap_bit_index);

  }else {
    std::cerr<<"template id "<<id_str<<" not found"<<'\n';
  }
}
