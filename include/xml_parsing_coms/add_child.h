//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_ADD_CHILD_H
#define EXCHANGEPARSER_ADD_CHILD_H

#endif // EXCHANGEPARSER_ADD_CHILD_H
#pragma once
#include <memory>
#include "Node.h"

inline void add_child(NODE* parent,
                      std::unique_ptr<NODE> new_child)
{
  if ( !parent || !new_child ) return;
  parent->children.push_back(std::move(new_child));
}

