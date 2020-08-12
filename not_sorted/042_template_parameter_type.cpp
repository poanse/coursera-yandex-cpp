#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
T Max(T a, T b) {
	if (b < a) {
		return a;
	}
	return b;
}

int main() {
	cout << max<double>(2, 3.5) << endl;
}
