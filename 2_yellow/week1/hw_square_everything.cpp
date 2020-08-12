#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <typename T> T Sqr(T x); 
template <typename K, typename V> pair<K, V> Sqr(pair<K, V> p);
template <typename T> vector<T> Sqr (vector<T> vec);
template <typename K, typename V> map<K, V> Sqr (map<K, V> mapping);

template <typename T>
vector<T> Sqr (vector<T> vec) {
	for (auto& x : vec) {
		x = Sqr(x);
	}
	return vec;
}

template <typename K, typename V>
map<K, V> Sqr (map<K, V> mapping) {
	for (auto& [key, value] : mapping) {
		value = Sqr(value);
	}
	return mapping;
}

template <typename K, typename V>
pair<K, V> Sqr (pair<K, V> p) {
	p.first = Sqr(p.first);
	p.second = Sqr(p.second);
	return p;
}

template <typename T>
T Sqr(T x) {
	return x * x;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> vec) {
	for (auto x : vec) {
		cout << x << ' ';
	}
	cout << '\b' << endl;
	return os;
}

int main() {// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
		{4, {2, 2}},
		{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}
