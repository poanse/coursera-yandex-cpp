#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main() {
	int x =5;
	x = 6;
	cout << x << endl; // outputs 6

	string s = "hello";
	string t = s;
	t += ", world";
	cout << "s = " << s << endl; // hello
	cout << "t = " << t << endl; // hello, world

	vector<string> w = {"a", "b", "c"};
	vector<string> v;
	v = w;
	v[0] = "d";

	cout << w[0] << " " << w[1] << endl;	
	cout << v[0] << " " << v[1] << endl;
}
