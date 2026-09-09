//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_PRINT_TREE_H
#define EXCHANGEPARSER_PRINT_TREE_H
#include <iostream>

#endif // EXCHANGEPARSER_PRINT_TREE_H
#pragma once
#include <memory>
#include "Node.h"

static void print_tree(const NODE* node,
                        const int depth = 0) {
  if (!node) return;

  std::string indent(depth * 4, ' ');

  std::cout << indent << "- Name: " << node->name
            << " | Type: " << node->type;

  if (!node->id.empty()) std::cout << " | ID: " << node->id;
  if (node->pmap) std::cout << " | PMAP: Yes";
  if (!node->opp.empty()) std::cout << " | Operator: " << node->opp;

  std::cout << "\n";

  // Recursively print all children
  for (const auto& child : node->children) {
    print_tree(child.get(), depth + 1);
  }
}
