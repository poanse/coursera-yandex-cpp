#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void PrintAvg() {
	vector<int> t = {-8, -7, 3};
	int sum = 0;
	for (int x : t) {
		sum += x;
	}
	int avg = (sum / t.size());
	cout << avg;
}

int main() {
	//cout << numeric_limits<int>::max() + 1 << " " <<
	//	numeric_limits<int>::min() - 1 << endl;
	int x = 2'000'000'000;
	int y = 1'000'000'000;
	cout << (x+y)/2 << endl;
	int xx = -2'000'000'000;
	unsigned int yy = xx;
	cout << xx << " " << yy << endl;

	int a = -1;
	unsigned b = 1;
	cout << (a < b) << endl;
	cout << (-1 < 1u) << endl;
	vector<int> vec = {4, 5};
	for (int i = 0;
			i < static_cast<int>(vec.size());
			++i) {
		cout << i << " " << vec[i] << endl;
	}
}
