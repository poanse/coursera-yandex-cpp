#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int x = 4;
	int y = 5;
	if (x==y){
		cout << "queal\n";
	} else {
		cout << "not equal\n";
	}

	// iterate over vector
	vector<int> vec = {1,3,5,6};
	for (auto x : vec){
		cout << x << ", ";
	}
	cout << "\n";

	// for
	int n = 5;
	int sum = 0;
	for (int i = 1; i <= n; ++i){
		sum += i;
	}
	cout << sum << "\n";
	
	// while
	int i = 1;
	sum = 0;
	while (i <= n){
		sum += i;
		++i;
	}	
	cout << sum << "\n";
}
