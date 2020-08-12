#include <random> 
#include <algorithm> 
#include <vector> 
#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	mt19937_64 random_gen;
	uint64_t sum = 0;
	for (int i = 0; i < n; ++i) {
		auto x = new uint64_t;
		*x = random_gen();
		sum += *x;
		delete x;
	}
	cout << sum;
}
