#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
	int n;
	cin >> n;
	deque<int> v(n);
	while (!v.empty()) {
		v.pop_front();
	}
	cout << "Empty!" << endl;
}
