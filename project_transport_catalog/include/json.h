#pragma once

#include <ios>
#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {
  struct Node;
  using Dict = std::map<std::string, Node>;

  struct Node : std::variant<
      Dict,
      std::vector<Node>,
      std::string,
      int,
      double,
      bool > 
  {
  public:

    using variant::variant;
    const variant& GetBase() const { return *this; }

    const auto& AsArray() const {
      return std::get<std::vector<Node>>(*this);
    }
    const auto& AsMap() const {
      return std::get<std::map<std::string, Node>>(*this);
    }
    int AsInt() const {
      return std::get<int>(*this);
    }
    bool AsBool() const {
      return std::get<bool>(*this);
    }
    double AsDouble() const {
      return std::get<double>(*this);
    }
    const auto& AsString() const {
      return std::get<std::string>(*this);
    }
  };

  class Document {
  public:
    explicit Document(Node root);

    const Node& GetRoot() const;

  private:
    Node root;
  };

  Document Load(std::istream& input);

  double GetDouble(const Json::Node& node);

  template <typename Value>
  void PrintValue(const Value& value, std::ostream& output) {
    output << value;
  }

  template <>
  void PrintValue<std::string>(const std::string& value, std::ostream& output);

  template <>
  void PrintValue<bool>(const bool& value, std::ostream& output);

  template <>
  void PrintValue<std::vector<Node>>(const std::vector<Node>& nodes, std::ostream& output);

  template <>
  void PrintValue<Dict>(const Dict& dict, std::ostream& output);

  void PrintNode(const Json::Node& node, std::ostream& output);
}
