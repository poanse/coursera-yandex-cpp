#include <iostream>
#include <map>
#include <string>
using namespace std;

void PrintMap(const map<int, string>& m) {
	cout << "Size = " << m.size() << endl;
	for (const auto& [key, value] : m) {
		cout << key << ": " << value << endl;;
	}
}

int main() {
	map<int, string> events;
	events[1950] = "Bjarne Stroustrup's birth";
	events[1941] = "Dennis Ritchie's birth";
	PrintMap(events);
	events.erase(1941);
	PrintMap(events);
}
