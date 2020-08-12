#include <iostream>
#include <vector>
#include <string>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& dest) {
	for (auto x : source) {
		dest.push_back(x);
	}
	source.clear();
}

int main() {
	vector<string> source = {"a", "b", "c"};
	vector<string> destination = {"z"};
	MoveStrings(source, destination);
	for (auto x : source) {
		cout << x << ' ';
	}
	cout << endl;
	for (auto x : destination) {
		cout << x << ' ';
	}
}

