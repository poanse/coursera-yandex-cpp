#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

ostream& operator<<(ostream& stream, vector<int> nums) {
	for (auto& x : nums) {
		cout << x << ' ';
	}
	return stream;
}



void Swap(int a, int b, vector<int>& nums) {
	int tmp = nums[a];
	nums[a] = nums[b];
	nums[b] = tmp;
}

void sortColorsRec(vector<int>& nums, int& l, int& m, int& r) {
	// l - first index after zeros
	// m - forst index after zeros and ones
	// r - index of new element
	if (nums[r] < nums[m]) {
		Swap(r, m, nums);
	}
	if (nums[m] < nums[l]) {
		Swap(m, l, nums);
	}
	if (nums[l] < 1) {
		l++;
	}
	if (nums[m] < 2) {
		m++;
	}
	if (r < nums.size() - 1) {
		r++;
		cout << l << ' ' << m << ' ' << r << "   ";
		cout << nums << '\n';
		sortColorsRec(nums, l, m, r);
	}
}

void sortColors(vector<int>& nums) {
	if (nums.size() != 1) {
		int l = 0;
		int m = 0;
		int r = 1;
		sortColorsRec(nums, l, m, r);
	}
}


int main() {
	vector<int> vec {2,0,2,1,1,0};
	cout << vec << '\n';
	sortColors(vec);
	cout << vec << '\n';
}
