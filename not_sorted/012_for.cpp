#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main() {
	vector<int> a = {1, 4, 6, 8, 10};
	int sum = 0;
	for (auto i : a){
		sum += i;
	}
	cout << sum << endl;


	sum = 0;
	string concat;
	map<string, int> b = {{"a", 1}, {"b", 2}, {"c", 3}};
	for (auto i : b) {
		concat += i.first;
		sum += i.second;
	}
	cout << concat << endl;
	cout << sum << endl;

	// range-based for
	string s = "asdagfdasgfrae";
	int i = 0;
	for (auto c : s) {
		if (c == 'a'){
			cout << i << endl;
		}
		++i;
	}

	// another for
	for (int i = 0; i < s.size(); ++i){
		if (s[i] == 'a') {
			cout << i << endl;
		}
	}

	// break
	for (int i = 0; i < s.size(); ++i){
		if (s[i] == 'a') {
			cout << i << endl;
			break;
		}
	}

}
