#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
int Min(int a, int b) {
	if (a<b) {
		return a;
	}
	return b;
}

int Max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
*/

void Print(const vector<int>& v, const string& title) {
	cout << title << ": ";
	for (auto i : v) {
		cout << i << ' ';
	}
	cout << endl;
}

int main() {
	/*
	cout << Min(2,3) << endl;
	cout << Max(2,3) << endl;
	*/
	cout << min(2,3) << endl;
	cout << max(2,3) << endl;
	cout << min("abc","bca") << endl;
	cout << max("abc","bca") << endl;
	vector<int> v {1,3,2,5,4};
	Print(v, "init");
	sort(begin(v), end(v));
	Print(v, "sorted");
}

