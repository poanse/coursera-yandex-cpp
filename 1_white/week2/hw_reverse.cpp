#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void Swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
void Reverse(vector<T>& dest) {
	for (auto i = 0; i < dest.size() / 2; i++) {
		Swap(dest[i], dest[dest.size() - 1 - i]);
	}
}

int main() {
	//vector<string> source = {"a", "b", "c", "e"};
	vector<int> source = {1,2,3,4};
	Reverse(source);
	for (auto x : source) {
		cout << x << ' ';
	}
	cout << endl;
}

