#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

struct NODE
{
  std::string name;
  std::string type;
  std::string id;

  bool pmap= false;
  bool optional= false;

  std::string opp;
  std::vector<std::unique_ptr<NODE>> children;
};

static void add_child(NODE* parent,
                      std::unique_ptr<NODE> new_child)
{
  if ( !parent || !new_child ) return;
  parent->children.push_back(std::move(new_child));
}

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
    else if (cppNODE->opp == "delta"||
      cppNODE->opp == "none") {
      cppNODE->pmap=false;
    }
  }
  return cppNODE;
}

//// remove
///////// remove later :(
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
//////////
//////

int main()
{
  std::unordered_map<std::string, std::unique_ptr<NODE>> template_registry;
  ////
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file("test2.xml");
  if (!result) {
    std::cerr << "XML parsing error: " << result.description() << '\n';
    return 1;
  }
  pugi::xml_node root = doc.document_element();
  for (pugi::xml_node child: root.children()) {
    std::unique_ptr<NODE>parsed_template = parse_child(child);
    if (!parsed_template->id.empty()) {
      template_registry[parsed_template->id] = std::move(parsed_template);
    }
  }
  std::cout << "Registry loaded with "<< template_registry.size() << " Templates <3 \n";
  ///

  //////// testing code
  for (const auto& pair : template_registry) {
    std::cout << "Map Key (Template ID): " << pair.first << "\n";
    print_tree(pair.second.get());
    std::cout << "--------------------------------------------------\n";
  }

  return 0;
}

void parser_func(std::unordered_map<std::string, std::unique_ptr<NODE>>& template_registry,
  std::string path)
{

}

