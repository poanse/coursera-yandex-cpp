#include <iostream>
#include <vector>
using namespace std;

void PrintVector(const vector<string>& v) {
	for (auto s : v) {
		cout << s << endl;
	}
}

int main() {
	int n;
	cin >> n;
	/*	
	vector<string> v(n);
	for (string& s : v) {
		cin >> s;
	}
	*/
	vector<string> v;
	string s;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		v.push_back(s);
		cout << "Current size = " << v.size() << endl;
	}
	PrintVector(v);
}
