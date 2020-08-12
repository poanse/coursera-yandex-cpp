#include <iostream>
#include <vector>

using namespace std;


int searchInsert(const vector<int>& nums, int target) {
	int n = nums.size();
	if (target > nums[n-1]) {
		return n;
	}
	int i = n / 2;
	int step_sum = n / 2;
	int step = 0;
	while (step_sum > 0) {
		step = step_sum / 2 + step_sum % 2;
		step_sum -= step;
		if (target == nums[i] || (target < nums[i] && target > nums[i-1])) {
			return i;
		} else if (target > nums[i]) {
			i += step;
		} else {
			i -= step;
		}
	}
	return i;
}

int main() {
	cout << searchInsert({1,2,3}, 5) << " " << "3" << '\n';
	cout << searchInsert({1,2,3}, 2) << " " << "1"  << '\n';
	cout << searchInsert({1,2,3}, 0) << " " << "0"  << '\n';
	cout << searchInsert({1,2,3,4,5}, 5) << " " << "4"  << '\n';
	cout << searchInsert({1,2,3,4,5,6}, 5) << " " << "4"  << '\n';
	cout << searchInsert({0,1,2,3,4,5}, 5) << " " << "5"  << '\n';
	cout << searchInsert({1,2,3,4}, 5) << " " << "4"  << '\n';
	cout << searchInsert({1}, 0) << " " << "0"  << '\n';
	cout << searchInsert({1,3,5,6}, 2) << " " << "1"  << '\n';
}
