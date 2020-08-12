#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int gcd(int a, int b) {
	if (b < a) {
		// swap so that a < b
		int tmp = a;
		a = b;
		b = tmp;
	}
	int c = b % a;
	if (c == 0) {
		return a;
	}
	return gcd(c, a);
}

int main() {
	int a, b;
	cin >> a >> b;
	cout << gcd(a, b);
}
