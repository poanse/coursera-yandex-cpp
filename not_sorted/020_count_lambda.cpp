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
	for (const auto& i : v) {
		cout << i << ' ';
	}
	cout << endl;
}

bool Gt2(int x) {
	if (x > 2) {
		return true;
	}
	return false;
}

int main() {
	vector<int> v {1,3,2,5,4};
	/*
	int cnt = 0;
	for (auto i : v){
		if (i == 2) {
			++cnt;
		}
	}
	cout << cnt << endl;
	*/
	// count
	//	cout << count(begin(v), end(v), 9) << endl;
	// count if
	//	cout << count_if(begin(v), end(v), Gt2) << endl;
	// lambda
	//	int thr = 0;
	//	cin >> thr;
	/*
	cout << count_if(begin(v), end(v), [thr](int x){if (x>thr){return true;}else{return false;}}) << endl;
	*/
	//	cout << count_if(begin(v), end(v), [thr](int x){return (x > thr);}) << endl;
	/*
	for (int i = 0; i < v.size(); ++i) {
		++v[i];
	}
	*/
	Print(v, "init");
	for (auto& i : v) {
		++i;
	}
	Print(v, "inc ");

}

