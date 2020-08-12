#include <iostream>
using namespace std;

int main() {
	size_t N, density;
	uint64_t w, h, d;
	uint64_t volume = 0;
	cin >> N >> density;
	for (size_t i = 0; i < N; i++) {
		cin >> w >> h >> d;
		volume += w * h * d;
	}
	cout << volume * density << endl;
}
