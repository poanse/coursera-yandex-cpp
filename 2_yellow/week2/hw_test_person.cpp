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
/*
class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
	  names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  surnames[year] = last_name;
  }
  string GetFullName(int year) {
	  string name = GetName(year, names);
	  string surname = GetName(year, surnames);
	  string output = "";
	  if (name == "n" && surname == "n") {
		  output = "Incognito";
	  } else if (name == "n") {
		  output = surname + " with unknown first name";
	  } else if (surname == "n") {
		  output = name + " with unknown last name";
	  } else {
		  output = name + ' ' + surname;
	  }
	  return output;
  }
private:
  map<int, string> names;
  map<int, string> surnames;
  string GetName(int year, map<int, string>& strings) {
	  string name;
	  if (strings.count(year)) {
		name = strings[year];
	  } else {
		int max_year = -10000;
		name = "n";
		for (auto& kv : strings) {
			if (kv.first < year && kv.first > max_year) {
				name = kv.second;
				max_year = kv.first;
			}
		}
	  }
	  return name;
  }
};
*/

void Test1() {
	Person person {};
	AssertEqual(person.GetFullName(1000), "Incognito", "empty");
	person.ChangeFirstName(2000, "Ivan");
	AssertEqual(person.GetFullName(1999), "Incognito", "empty2");
	AssertEqual(person.GetFullName(2000), "Ivan with unknown last name", "name only");
	AssertEqual(person.GetFullName(2001), "Ivan with unknown last name", "name only");
	person.ChangeLastName(2005, "Smirnov");
	AssertEqual(person.GetFullName(1999), "Incognito", "empty2");
	AssertEqual(person.GetFullName(2001), "Ivan with unknown last name", "name only 2");
	AssertEqual(person.GetFullName(2007), "Ivan Smirnov", "both");
	person.ChangeLastName(2005, "Smirnoff");
	AssertEqual(person.GetFullName(1999), "Incognito", "empty2");
	AssertEqual(person.GetFullName(2000), "Ivan with unknown last name", "name only 2");
	AssertEqual(person.GetFullName(2001), "Ivan with unknown last name", "name only 2");
	AssertEqual(person.GetFullName(2007), "Ivan Smirnoff", "both");
	person.ChangeFirstName(2000, "Ivanko");
	AssertEqual(person.GetFullName(1999), "Incognito", "empty2");
	AssertEqual(person.GetFullName(2000), "Ivanko with unknown last name", "name only 2");
	AssertEqual(person.GetFullName(2001), "Ivanko with unknown last name", "name only 2");
	AssertEqual(person.GetFullName(2007), "Ivanko Smirnoff", "both");
}

void Test2 () {
	Person person {};
	person.ChangeLastName(2000, "Smirnov");
	AssertEqual(person.GetFullName(1999), "Incognito", "empty2");
	AssertEqual(person.GetFullName(2000), "Smirnov with unknown first name", "name only");
	AssertEqual(person.GetFullName(2001), "Smirnov with unknown first name", "name only");
	person.ChangeFirstName(1995, "Ivan");
	AssertEqual(person.GetFullName(1994), "Incognito", "empty2");
	AssertEqual(person.GetFullName(1997), "Ivan with unknown last name", "empty2");
	AssertEqual(person.GetFullName(2000), "Ivan Smirnov", "name only");
	AssertEqual(person.GetFullName(2001), "Ivan Smirnov", "name only");
}

int main() {
  TestRunner runner;
  runner.RunTest(Test1, "test 1");
  runner.RunTest(Test2, "test 2");
  // добавьте сюда свои тесты
  return 0;
}
