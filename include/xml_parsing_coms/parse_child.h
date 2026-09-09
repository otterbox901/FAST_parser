#pragma once
#include "FastValue+StateDic.h"
#include "add_child.h"
#include "pugixml.hpp"
#include <string>
#include <variant>
#include <vector>
#include <cstdint>


inline FastValue parse_initial_value(const std::string& val_str, const std::string& type)
{
  if (val_str.empty()) return std::string{};

  if (type == "uInt32" || type == "length") {
    return static_cast<uint32_t>(std::stoul(val_str));
  }
  if (type == "uInt64") {
    return std::stoull(val_str);
  }
  if (type == "int32") {
    return std::stoi(val_str);
  }
  if (type == "int64") {
    return std::stoll(val_str);
  }
  if (type == "decimal") {
    return std::stod(val_str);
  }
  if (type == "byteVector") {
    return std::vector<uint8_t>(val_str.begin(), val_str.end());
  }
  return val_str;
}

//// above is a helper to parse operator initial values

static std::unique_ptr<NODE> parse_child(const pugi::xml_node xml_root)
{
  auto cppNODE = std::make_unique<NODE>();
  cppNODE->name= xml_root.attribute("name").value();
  cppNODE->type= xml_root.name();

  std::string presence= xml_root.attribute("presence").value();
  if (presence == "optional"){
    cppNODE->optional= true;
  }

  if (cppNODE->type=="template") {
    cppNODE->pmap=true;
    cppNODE->id = xml_root.attribute("id").value();
  }

  if (cppNODE->type == "template" || cppNODE->type == "sequence" || cppNODE->type == "group") {
    cppNODE ->pmap=true;
    for (pugi::xml_node child: xml_root.children()) {
      add_child(cppNODE.get(),parse_child(child));
    }
  }
  else{
    pugi::xml_node opp=  xml_root.first_child();
    if (opp) {
      cppNODE->opp= opp.name();
      std::string raw_val = opp.attribute("value").value();
      cppNODE->initial_value= parse_initial_value(raw_val, cppNODE->type);
    }
    else {
      cppNODE->opp= "none";
    }

    if (cppNODE->opp == "copy" ||cppNODE->opp == "tail" ||
      cppNODE->opp == "default" ||cppNODE->opp == "increment") {
      cppNODE->pmap=true;
      }
    else if (cppNODE->opp == "constant") {
      cppNODE->pmap=cppNODE->optional;
    }
    else if (cppNODE->opp == "delta"||cppNODE->opp == "none") {
      cppNODE->pmap=false;
    }
  }
  return cppNODE;
}