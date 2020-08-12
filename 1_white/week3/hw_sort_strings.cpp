#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;


template<typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
	if (v.size() == 0) {
		return os;
	}
	if (v.size() == 1) {
		os << v[0];
		return os;
	}
	auto it = v.begin();
	while (it != prev(v.end())) {
		os << *it << ' ';
		it++;
	}
	os << *it;
	return os;
}

bool compare(string lhs, string rhs) {
	for (auto& c : lhs) {
		c = tolower(c);
	}
	for (auto& c : rhs) {
		c = tolower(c);
	}
	return lhs < rhs;
}

int main() {
	vector<string> strings;
	int N;
	string k;
	cin >> N;
	for (auto i = 0; i < N; i++) {
		cin >> k;
		strings.push_back(k);
	}
	sort(begin(strings), end(strings), compare);
	cout << strings << endl;
}
