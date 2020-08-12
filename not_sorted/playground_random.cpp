#include <random>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;

int main() {
	vector<int> weights = {1,2,3,4,5};
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);
	discrete_distribution<int> distribution (weights.begin(), weights.end());

	for (int i = 0; i < 10; ++i) {
		cout <<	distribution(generator) << " ";
	}
	cout << endl;
}
