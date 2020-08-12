#include <iostream>

using namespace std;

int Factorial(int a) {
	if (a <= 0) {
		return 1;
	}
	return a * Factorial(a - 1);
}

int main() {
	int a;
	cin >> a;
	cout << Factorial(a);
}
