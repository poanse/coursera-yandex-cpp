#include <iostream>
#include <map>

using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& mapping, K key) {
	if (0 == mapping.count(key)) {
		throw runtime_error("123");
	}
	return mapping[key];
}

int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	GetRefStrict(m, 10);
}
