#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

template<typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
	if (v.size() == 0) {
		return os;
	}
	if (v.size() == 1) {
		os << v[0];
		return os;
	}
	auto it = v.begin();
	while (it != prev(v.end())) {
		os << *it << ' ';
		it++;
	}
	os << *it;
	return os;
}

int main() {
	vector<int> numbers;
	int N, k;
	cin >> N;
	for (auto i = 0; i < N; i++) {
		cin >> k;
		numbers.push_back(k);
	}
	sort(begin(numbers), end(numbers), 
			[](int lhs, int rhs){
				return abs(lhs) < abs(rhs);
			}
	);
	cout << numbers << endl;
}
