#ifndef EXCHANGEPARSER_NODE_H
#define EXCHANGEPARSER_NODE_H
#include "FastValue+StateDic.h"

#include <memory>
#endif // EXCHANGEPARSER_NODE_H
# pragma once
#include <string>
#include <vector>

struct NODE
{
  std::string name;
  std::string type;
  std::string id;

  bool pmap= false;
  bool optional= false;

  std::string opp;
  FastValue initial_value; /// this is for ops
  std::vector<std::unique_ptr<NODE>> children;
};


