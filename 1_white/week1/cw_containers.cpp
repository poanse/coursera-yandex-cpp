#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	string s = "abcdefg";
	for (char c : s) {
		cout << c << ",";
	}
	cout << "\n";

	vector<int> nums = {1, 2, 3, 5, 4 ,2};
	for (auto c : nums) {
		cout << c << ",";
	}
	cout << "\n";

	int quantity = 0;
	for (auto x : nums) {
		if (x == 5){
			++quantity;
		}
	}
	cout << "There are " << quantity << " fives\n";
	quantity = count(begin(nums), end(nums), 5);
	cout << quantity << "\n";

	sort(begin(nums), end(nums));
	cout << "After sorting:\n";
	for (auto c : nums) {
		cout << c << ",";
	}
	cout << "\n";

}
