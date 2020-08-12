#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

//bool IsPalindrom(const string& str) {
  //// Вы можете вставлять сюда различные реализации функции,
  //// чтобы проверить, что ваши тесты пропускают корректный код
  //// и ловят некорректный
//}

void TestTrivial() {
	{
		string str = "";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = "a";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = "1";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = "aa";
		AssertEqual(IsPalindrom(str), true, "");
	}
}

void TestSimple() {
	{
		string str = "aba";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = "ab";
		AssertEqual(IsPalindrom(str), false, "");
	}
	{
		string str = "abb";
		AssertEqual(IsPalindrom(str), false, "");
	}
	{
		string str = "bba";
		AssertEqual(IsPalindrom(str), false, "");
	}
	{
		string str = "123abcdeedcba321";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = "123abcdefdcba321";
		AssertEqual(IsPalindrom(str), false, "");
	}
}

void TestSpaces() {
	{
		string str = " ";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = "  ";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = " a";
		AssertEqual(IsPalindrom(str), false, "");
	}
	{
		string str = "a ";
		AssertEqual(IsPalindrom(str), false, "");
	}
	{
		string str = "   ";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = " aba ";
		AssertEqual(IsPalindrom(str), true, "");
	}
	{
		string str = " 123a bcde edcb a321 ";
		AssertEqual(IsPalindrom(str), true, "");
	}
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestTrivial, "test trivial");
  runner.RunTest(TestSimple, "test simple");
  runner.RunTest(TestSpaces, "test spaces");
  return 0;
}
