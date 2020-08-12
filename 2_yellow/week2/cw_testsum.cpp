#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

int Sum(int x, int y) {
	return x + y;	
};

void TestSum() {
	assert(Sum(2, 3) == 5);
	assert(Sum(-2, -3) == -5);
	assert(Sum(-2, 0) == -2);
	assert(Sum(-2, 2) == 0);
	cout << "TestSum OK" << endl;
}

template <typename T, typename U>
AssertEqual (const T& t, const U& u, const string& hint) {
	if (t != u) {
		ostreamstream os;
		os << "Assertion failed: " << t << " != " << u
			<< "Hint: " << hint;
		throw runtime_error(os.str());
	}

}

int main() {
	TestSum();

}
