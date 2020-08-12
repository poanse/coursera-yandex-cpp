#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main() {
	int a = 3;
	int b = 5;

	cout << (a==b) << endl;

	string c = "fire";
	string d = "water";
	cout << (c < d) << endl;

	vector<string> f = {"fire", "water"};
	vector<string> g = {"fog", "air"};
	cout << (f < g) << endl;

	string s = "abc";
	if (!s.empty() && s < "zzz") { // && - and, || - or
		cout << s << endl;
	}
}
