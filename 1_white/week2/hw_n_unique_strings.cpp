#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<string> rows(n);
	for (auto& row : rows) {
		cin >> row;
	}
	set<string> unique_rows(begin(rows), end(rows));
	cout << unique_rows.size() << endl;
}
