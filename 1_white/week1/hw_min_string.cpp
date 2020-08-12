#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	vector<string> strings;
	for (auto i = 0; i < 3; i++) {
		string tmp;
		cin >> tmp;
		strings.push_back(tmp);
	}
	sort(strings.begin(), strings.end());
	cout << strings[0];
}
