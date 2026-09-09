//
// Created by alex on 2026-08-19.
//

#ifndef EXCHANGEPARSER_PARSER_FUNC_H
#define EXCHANGEPARSER_PARSER_FUNC_H
#include <iostream>
#include <unordered_map>

#endif // EXCHANGEPARSER_PARSER_FUNC_H
#include "Node.h"
#include "parse_child.h"
#include "add_child.h"

inline void parser_func(
    std::unordered_map<std::string, std::unique_ptr<NODE>> & template_registry,
  std::string& path)
{
  pugi::xml_document doc;
  if (pugi::xml_parse_result result = doc.load_file("test2.xml"); !result) {
    std::cerr << "XML parsing error: " << result.description() << '\n';
  }
  for (const pugi::xml_node root = doc.document_element();
       const pugi::xml_node child: root.children()) {
    std::unique_ptr<NODE>parsed_template = parse_child(child);
    if (!parsed_template->id.empty()) {
      template_registry[parsed_template->id] = std::move(parsed_template);
    }
  }
  std::cout << "Registry loaded with "<< template_registry.size() << " Templates <3 \n";
}
