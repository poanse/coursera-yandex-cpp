#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> T(n);
	for (int i = 0; i < n; ++i) {
		cin >> T[i];
	}
	// calculate mean
	long int mean = 0;
	for (auto x : T) {
		mean += x;
	}
	mean = mean / n;
	// find K
	int K = 0;
	for (auto x : T) {
		if (x > mean) {
			++K;
		}
	}
	cout << K << endl;
	for (int i = 0; i < n; ++i) {
		if (T[i] > mean) {
			cout << i << " ";
		}
	}
	cout << endl;
	// output indexes where T > meanT


}
