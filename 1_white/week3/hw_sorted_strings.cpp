#include <string>
#include <vector>
#include <iostream>
using namespace std;

class SortedStrings {
public:
	void AddString(const string& s) {
		if (strings.size() != 0) {
			auto it = strings.begin();
			while ((it != strings.end()) && (s > *it)) {
				++it;
			}
			strings.insert(it, s);
		} else {
			strings.push_back(s);
		}
	}
	vector<string> GetSortedStrings() {
		return strings;
	}
private:
	vector<string> strings;
};
/*
int main() {
	SortedStrings sorted_strings;
	sorted_strings.AddString("second");
	sorted_strings.AddString("first");
	sorted_strings.AddString("third");
	sorted_strings.AddString("second");
	for (const auto& s : sorted_strings.GetSortedStrings()) {
		cout << s << " ";
	}
	cout << endl;
}
*/
