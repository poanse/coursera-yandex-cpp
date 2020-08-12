#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main() {
	vector<int> t = {-8, -7, 3};
	int sum = 0;
	for (int x : t) {
		sum += x;
	}
	int avg = sum / t.size();
	cout << avg << endl;

	int x = 2'000'000'000;
	cout << x << " ";
	x *= 2;
	cout << x << " ";

	// int: 32 bits, -2^31 to 2^31 - 1
	// unsigned int (unsigned): 32bits, 0 to 2^32 - 1
	// size_t: 32 or 64 bits (depending on the OS)
	// cstdint
	// int32_t, uint32_t - 32 bits are guaranteed
	// ints or uints: 8, 16, 32, 64
	cout << sizeof(x) << endl;
	cout << numeric_limits<long int>::min() << " " << numeric_limits<long int>::max() << endl;
}
