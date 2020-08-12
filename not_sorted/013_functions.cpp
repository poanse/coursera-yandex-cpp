#include <iostream>
using namespace std;

void ChangeInt(int& x) {
	x = 42;
}

int main() {
	int a = 5;
	ChangeInt(a);
	cout << a << endl;
}
