#include "json.h"

using namespace std;

namespace Json {

  Document::Document(Node root) 
  : root(move(root)) 
  {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }
    return Node(move(result));
  }

  Node LoadInt(istream& input) {
		int result = 0;
		while (isdigit(input.peek())) {
			result *= 10;
			result += input.get() - '0';
		}
    return Node(result);
  }

  Node LoadDouble(istream& input) {
		double result = 0;
		input >> result;
    return Node(result);
  }
	Node LoadNumber(istream& input) {
		string str;
		for (char c = input.peek(); (isdigit(c) || (c == '.') || (c == '-'));) {
			str += input.get();
			c = input.peek();
		}
		if (str.find('.') != string::npos){
			double result = strtod(str.c_str(), nullptr);
			return Node(result);
		} else {
			int result = atoi(str.c_str());
			return Node(result);
		}
	}

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }

  Node LoadBool(istream& input) {
    string line;
		for (char c; input >> c;) {
			if (c == ' ' || c == '\n' || c == ',' || c == '}') {
				input.putback(c);
				break;
			}
			line += c;
		}
		if (line == "false") {
			return Node(false);
		} else if (line == "true") {
			return Node(true);
		} else {
			throw invalid_argument(line + " is not bool");
		}
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else if (c == 't' || c == 'f') {
      input.putback(c);
      return LoadBool(input);
    } else {
      input.putback(c);
      return LoadNumber(input);
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

  template <>
  void PrintValue<std::string>(const std::string& value, std::ostream& output) {
    output << '\"' << value << '\"';
  }

  template <>
  void PrintValue<bool>(const bool& value, std::ostream& output) {
    output << std::boolalpha << value;
  }

  template <>
  void PrintValue<std::vector<Node>>(const std::vector<Node>& nodes, std::ostream& output) {
    output << '[';
    bool first = true;
    for (const auto& x : nodes) {
      if (first) {
        first = false;
      } else {
        output << ", ";
      }
      PrintNode(x, output);
    }
    output << ']';
  }

  template <>
  void PrintValue<Dict>(const Dict& dict, std::ostream& output) {
    output << '{';
    bool first = true;
    for (const auto& [key, value] : dict) {
      if (first) {
        first = false;
      } else {
        output << ", ";
      }
      PrintValue(key, output);
      output << ": ";
      PrintNode(value, output);
    }
    output << '}';
  }
  
  void PrintNode(const Json::Node& node, std::ostream& output) {
    std::visit([&output](const auto& value) { PrintValue(value, output); }, node.GetBase());
  }

}