#ifndef EXCHANGEPARSER_FASTVALUE_STATEDIC_H
#define EXCHANGEPARSER_FASTVALUE_STATEDIC_H
#pragma once
#include <variant>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>


using FastValue= std::variant<uint32_t, uint64_t, int64_t, int32_t, double, std::string, std::vector<uint8_t>>;
using StateDictionary= std::unordered_map<std::string, FastValue>;

#endif // EXCHANGEPARSER_FASTVALUE_STATEDIC_H