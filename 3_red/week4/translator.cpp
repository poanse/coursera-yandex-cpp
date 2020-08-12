#include "test_runner.h"
#include <string>
#include <string_view>
#include <vector>
#include <map>
using namespace std;

class Translator {
public:
  Translator() {}
  void Add(string_view source, string_view target) {
	//char *s = new char[source.size() + 1];
	//size_t length = source.copy(s, source.size());
	//s[length] = '\0';
	//char *t = new char[target.size() + 1];
	//length = target.copy(t, target.size());
	//t[length] = '\0';
	//const string_view s_view(s);
	//const string_view t_view(t);
	auto s_view = Clone(source);
	auto t_view = Clone(target);
	data_f[s_view] = t_view;
	data_b[t_view] = s_view;
  }
  string_view TranslateForward(string_view source) const {
	return Translate(data_f, source);
  }

  string_view TranslateBackward(string_view target) const {
	return Translate(data_b, target);
  }

private:
  map<string_view, string_view> data_f;
  map<string_view, string_view> data_b;

  const string_view Clone(string_view str) {
	auto it = data_f.find(str);
	if (it != data_f.end()) {
		return it->first;
	}
	it = data_b.find(str);
	if (it != data_b.end()) {
		return it->first;
	}
	char *s = new char[str.size() + 1];
	size_t length = str.copy(s, str.size());
	s[length] = '\0';
	return s;
  }

  static string_view Translate(const map<string_view, string_view>& dict, string_view value) {
	if (const auto it = dict.find(value); it != dict.end()) {
      return it->second;
    } else {
      return {};
    }
  }
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  //for (auto& [key,value] : translator.data_f) {
	  //cout << key << ' ' << value << endl;
  //}
  //cout << endl;
  translator.Add(string("stol"), string("table"));
  //for (auto& [key,value] : translator.data_f) {
	  //cout << key << ' ' << value << endl;
  //}
  //cout << (translator.TranslateForward("okno") == "window") << endl;
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
