#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<char, int> BuildCharCounters(string word) {
	map<char, int> counts;
	for (const auto& c : word) {
		++counts[c];
	}
	return counts;
}

int main() {
	int n;
	cin >> n;
	vector<vector<string> > word_pairs(n);

	string tmp1, tmp2;
	for (auto& item : word_pairs) {
		cin >> tmp1 >> tmp2;
		item.push_back(tmp1);
		item.push_back(tmp2);
	}
	for (const auto& item : word_pairs) {
		if (BuildCharCounters(item[0]) ==  BuildCharCounters(item[1])) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}
