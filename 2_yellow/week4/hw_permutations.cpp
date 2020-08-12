#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

ostream& operator<< (ostream& os, vector<size_t> v) {
	auto it = v.begin();
	while(it != prev(v.end())) {
		cout << *it++ << ' ';
	}
	cout << *it;
	return os;
}

int main() {
	size_t N;
	cin >> N;
	vector<size_t> v(N);
	for (size_t i = 0; i < N; i++) {
		v[i] = N - i;
	}
	cout << v << endl;
	while (prev_permutation(v.begin(), v.end())) {
		cout << v << endl;
	}

}
