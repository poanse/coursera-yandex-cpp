#include <iostream>
#include <utility>
#include <sstream>
#include <vector>
#include <map>
using namespace std;


template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, 
		const pair<First, Second>& p2) {
	
	First f = p1.first * p2.first;
	Second s = p1.second * p2.second;
	return make_pair(f, s);
}

template <typename T>
T Sqr(T x) {
	return x * x;
}

template <typename T>
ostream& operator<< (ostream& out, const vector<T>& vi) {
	for (const T& i : vi) {
		cout << i << ' ';
	}
	return out;
}

template <typename K, V>
ostream& operator<< (ostream& out, const map<K,V>& vi) {
	for (const auto& [key, value] : vi) {
		cout << key << ' ' << value << '\n';
	}
	return out;
}



int main() {
	auto p = make_pair(2.5,3);
	auto res = Sqr(p);
	cout << res.first << endl;
	cout << res.second << endl;

	vector<int> vi = {1,2,3};
	cout << vi;

	map<int, int> m = {{1,2}, {3,4}};
	cout << m << endl;
}
