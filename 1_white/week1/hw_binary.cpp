#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> chars;
	while (N > 0) {
		chars.push_back(N % 2);
		N = N / 2;
	}
	for (auto i = chars.size(); i > 0; i--) {
		cout << chars[i-1];
	}
}
