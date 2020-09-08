#pragma once

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

  struct Node : std::variant<
      std::map<std::string, Node>,
      std::vector<Node>,
      std::string,
      int,
      double,
      bool > 
  {
  public:

    using variant::variant;

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
}

std::ostream& operator<<(std::ostream& os, const Json::Node& node);