#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main() {
	int a = 11;
	int b = 3;
	cout << a / b << endl; // 3

	double c = 3;
	cout << a / c << endl; // 3.66667

	int x = 5;
	// x = x + 1
	// x += 1
	// x++
	// ++x

	int k = x++;
	int l = ++x;
	cout << "k = " << k << endl;
	cout << "l = " << l << endl;
}
