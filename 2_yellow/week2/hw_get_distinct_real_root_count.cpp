#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
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

template <typename T>
double helper(T a, T b, T c) {
	return (c - b * b / 4 / a);
}

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  if (a > 0 && helper(a, b, c) > 0) {
	  return 0;
  } else if (a > 0 && helper(a, b, c) < 0) {
	  return 2;
  } else if (a == 0 && b == 0) {
	  return 0;
  } else if (a == 0) {
	  return 1;
  } else if (a < 0 && helper(a, b, c) < 0) {
	  return 0;
  } else if (a < 0 && helper(a, b, c) > 0) {
	  return 2;
  } else if (helper(a, b, c) == 0) {
	  return 1;
  }
  return 0;
}


void Test1(){
	AssertEqual(GetDistinctRealRootCount(1,0,9), 0, "test 1a");
	AssertEqual(GetDistinctRealRootCount(1,2,9), 0, "test 1b");
	AssertEqual(GetDistinctRealRootCount(1,-10,100), 0, "test 1c");
	AssertEqual(GetDistinctRealRootCount(1,10,100), 0, "test 1d");
	AssertEqual(GetDistinctRealRootCount(100,-10,100), 0, "test 1e");
	AssertEqual(GetDistinctRealRootCount(100,10,100), 0, "test 1f");
}

void Test2(){
	AssertEqual(GetDistinctRealRootCount(1,0,-9), 2, "test 2a");
	AssertEqual(GetDistinctRealRootCount(10,0,-9), 2, "test 2b");
	AssertEqual(GetDistinctRealRootCount(100,0,-9), 2, "test 2c");
	AssertEqual(GetDistinctRealRootCount(1,5,-9), 2, "test 2d");
	AssertEqual(GetDistinctRealRootCount(1,100,-9), 2, "test 2e");
	AssertEqual(GetDistinctRealRootCount(1,-100,-9), 2, "test 2f");
	AssertEqual(GetDistinctRealRootCount(100,-100,10), 2, "test 2g");
}

void Test3(){
	AssertEqual(GetDistinctRealRootCount(0,1,3), 1, "test 3a");
	AssertEqual(GetDistinctRealRootCount(0,1,-3), 1, "test 3b");
	AssertEqual(GetDistinctRealRootCount(0,-1,3), 1, "test 3c");
	AssertEqual(GetDistinctRealRootCount(0,-1,-3), 1, "test 3d");
	AssertEqual(GetDistinctRealRootCount(0,100,3), 1, "test 3e");
	AssertEqual(GetDistinctRealRootCount(0,1,300), 1, "test 3f");
	AssertEqual(GetDistinctRealRootCount(0,100,300), 1, "test 3g");
	AssertEqual(GetDistinctRealRootCount(0,-100,3), 1, "test 3h");
	AssertEqual(GetDistinctRealRootCount(0,1,-300), 1, "test 3i");
}

void Test4(){
	AssertEqual(GetDistinctRealRootCount(-1,0,-1), 0, "test 4a");
	AssertEqual(GetDistinctRealRootCount(-1,0,-100), 0, "test 4b");
	AssertEqual(GetDistinctRealRootCount(-100,0,-1), 0, "test 4c");
	AssertEqual(GetDistinctRealRootCount(-100,0,-100), 0, "test 4d");
	AssertEqual(GetDistinctRealRootCount(-10,-10,-3), 0, "test 4e");
	AssertEqual(GetDistinctRealRootCount(-10,10,-100), 0, "test 4f");
}

void Test5(){
	AssertEqual(GetDistinctRealRootCount(-1,0,9), 2, "test 5a");
	AssertEqual(GetDistinctRealRootCount(-100,0,9), 2, "test 5b");
	AssertEqual(GetDistinctRealRootCount(-1,0,900), 2, "test 5c");
	AssertEqual(GetDistinctRealRootCount(-100,0,900), 2, "test 5d");
	AssertEqual(GetDistinctRealRootCount(-1,10,9), 2, "test 5e");
	AssertEqual(GetDistinctRealRootCount(-10,-10,900), 2, "test 5f");
	AssertEqual(GetDistinctRealRootCount(-10,-10,-1), 2, "test 5g");
}

void Test6(){
	AssertEqual(GetDistinctRealRootCount(100,0,0), 1, "test 6a");
	AssertEqual(GetDistinctRealRootCount(-100,0,0), 1, "test 6b");
	AssertEqual(GetDistinctRealRootCount(5,10,5), 1, "test 6c");
	AssertEqual(GetDistinctRealRootCount(-5,10,-5), 1, "test 6d");
	AssertEqual(GetDistinctRealRootCount(-5,-10,-5), 1, "test 6e");
	AssertEqual(GetDistinctRealRootCount(4,4,1), 1, "test 6f");
}

void Test7(){
	AssertEqual(GetDistinctRealRootCount(1,4, 0), 2, "test 6a");
	AssertEqual(GetDistinctRealRootCount(1,-4, 0), 2, "test 6b");
	AssertEqual(GetDistinctRealRootCount(-1,-4, 0), 2, "test 6c");
	AssertEqual(GetDistinctRealRootCount(-1,4, 0), 2, "test 6d");
	AssertEqual(GetDistinctRealRootCount(0,-4, 0), 1, "test 6e");
	AssertEqual(GetDistinctRealRootCount(0,4, 0), 1, "test 6f");
}

void Test8(){
	AssertEqual(GetDistinctRealRootCount(0,-4, 0), 1, "test 6a");
	AssertEqual(GetDistinctRealRootCount(0,-400, 0), 1, "test 6b");
	AssertEqual(GetDistinctRealRootCount(0,4, 0), 1, "test 6c");
	AssertEqual(GetDistinctRealRootCount(0,400, 0), 1, "test 6d");
}

void Test9(){
	AssertEqual(GetDistinctRealRootCount(0,0, -400), 0, "test 9a");
	AssertEqual(GetDistinctRealRootCount(0,0, -0.5), 0, "test 9b");
	AssertEqual(GetDistinctRealRootCount(0,0, 0.5), 0, "test 9c");
	AssertEqual(GetDistinctRealRootCount(0,0, 400), 0, "test 9d");
}

void MaxTest(){
	AssertEqual(GetDistinctRealRootCount(1,numeric_limits<double>::max(),0), 2, "1");
	AssertEqual(GetDistinctRealRootCount(numeric_limits<double>::max(),1,0), 1, "2");
	AssertEqual(GetDistinctRealRootCount(numeric_limits<double>::max(),
										 numeric_limits<double>::max(), 0), 1, "3");
	AssertEqual(GetDistinctRealRootCount(numeric_limits<double>::max(),
										 numeric_limits<double>::max(),
										 numeric_limits<double>::max()), 1, "4");
}

int main() {
  TestRunner runner;
  runner.RunTest(Test1, "test 1");
  runner.RunTest(Test2, "test 2");
  runner.RunTest(Test3, "test 3");
  runner.RunTest(Test4, "test 4");
  runner.RunTest(Test5, "test 5");
  runner.RunTest(Test6, "test 6");
  runner.RunTest(Test7, "test 7");
  runner.RunTest(Test8, "test 8");
  runner.RunTest(Test9, "test 9");
  runner.RunTest(MaxTest, "test Max");
  // добавьте сюда свои тесты
  return 0;
}
