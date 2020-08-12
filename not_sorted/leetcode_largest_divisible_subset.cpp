#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

template <typename Collection>
string Join(const Collection& c, char d) {
	stringstream ss;
	bool first = true;
	for (const auto& i : c) {
		if (!first) {
			ss << d;
		}
		first = false;
		ss << i;
	}
	return ss.str();
}

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1,T2>& vi) {
	return out << '(' << vi.first << ',' << vi.second << ')';
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& vi) {
	return out << '[' << Join(vi, ',') << ']';
}

template <typename T, typename T2>
ostream& operator<<(ostream& out, const map<T,T2>& m) {
	return out << '{' << Join(m, ',') << '}';
}




bool isValid(int a, int b) {
	return (((a % b) == 0) || ((b % a) == 0));
}

pair<bool, int> minKey(map<int, int>& counts) {
	if (counts.size() < 2) {
		return make_pair(false, 0);
	}
	int min_value = 999;
	int minKey = 0;
	for (auto& [key, value] : counts) {
		if (value < min_value) {
			min_value = value;
			minKey = key;
		}
	}
	if (min_value >= counts.size() - 1) {
		return make_pair(false, minKey);	
	}
	return make_pair(true, minKey);
}

map<int, int> check(const vector<int>& nums) {
	map<int, int> counts;
	int i = 0;
	int j = 0;
	int n = nums.size();
	while (i < n - 1) {
		j = i + 1;
		while (j < n) {
			int tmp = isValid(nums[i], nums[j]);
			counts[i] += tmp;
			counts[j] += tmp;
			j += 1;
		}
		i++;
	}
	return counts;
}

vector<int> largestDivisibleSubset(vector<int>& nums) {
	if (nums.size() < 2) {
		return nums;
	}
	map<int, int> counts = check(nums);
	auto mypair = minKey(counts);
	while (mypair.first == true) {
		counts.erase(mypair.second);
		cout << counts << endl;
		for (auto& [key, value] : counts) {
			if (isValid(nums[key], nums[mypair.second])) {
				value -= 1;
			}
		}
		//nums.erase(nums.begin() + mypair.second);
		cout << counts << endl;
		mypair = minKey(counts);
		cout << mypair << endl;
	}
	vector<int> output;
	for (auto& [key,value] : counts) {
		output.push_back(nums[key]);
	}
	return output;
}

int main () {
	vector<int> v1 {546, 669, 3};
	cout << v1 << '\n';
	cout << largestDivisibleSubset(v1) << endl;
	vector<int> v2 {1,2,4,8,9};
	cout << v2 << '\n';
	cout << largestDivisibleSubset(v2);
	vector<int> v3 {2,3,4,9,8};
	cout << v3 << '\n';
	cout << largestDivisibleSubset(v3);
}
