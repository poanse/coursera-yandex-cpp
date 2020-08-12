#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

int main () {
	set<string> famous_persons;
	famous_persons.insert("Stroustrup");
	famous_persons.insert("Ritchie");
	famous_persons.erase("Ritchie");
	for (auto x : famous_persons) {
		cout << x << endl;
	}

	vector<string> v = {"a", "b", "a"};
	set<string> s(begin(v), end(v));
	for (auto x : s) {
		cout << x << endl;
	}
}
