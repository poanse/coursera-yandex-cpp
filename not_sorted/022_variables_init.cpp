#include <iostream>
#include <string>
#include <vector>
using namespace std;

void PrintInt() {
	int x;
	cout << x << endl;
}

void PrintDouble() {
	double pi = 3.14;
	cout << pi << endl;
}

void PrintParity(int x) {
	/*
	string parity;

	if (x % 2 == 0){
		parity = "even";
	} else {
		parity = "odd";
	}
	*/

	string parity = (x % 2 == 0) ? "even" : "odd";
	cout << x << " is " << parity << endl;
}

void PrintPositivity(int x) {
	string positivity;
	if (x > 0) {
		positivity = "positive";
	} else if (x < 0) {
		positivity = "negative";
	} else {
		positivity = "zero";
	}
	cout << x << " is " << positivity << endl;
}

string GetPositivity(int x) {
	if (x > 0) {
		return "positive";
	} else if (x < 0) {
		return "negative";
	} else {
		return "zero";
	}
}

void PrintPositivity2(int x) {
	string positivity = GetPositivity(x);
	cout << x << " is " << positivity << endl;
}


int main () {
	PrintInt();
	PrintDouble();
	PrintInt();
	PrintParity(6);
	PrintPositivity(6);
	PrintPositivity2(6);
}

