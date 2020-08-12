#include<iostream>
#include<string>
using namespace std;

int main() {
	string a = "abc";
	string b = "def";
	int x = 4;
	int y = 5;
	cout << (x + y) * (x - y) << "\n";
	if (x == y) {
		cout << "x equal y\n";
	} else {
		cout << "x not equal y\n";
	}
	if (a != b) {
		cout << "a not equal b\n";
	} else {
		cout << "a equal b\n";
	}

	if (a < b) {
		cout << "a less than b\n";
	} else {
		cout << "a not less than b\n";
	}
	return 0;
}
