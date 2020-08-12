#include <iostream>
#include <list>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <sstream>
//#include "profile.h"
using namespace std;

int main() {
	stringstream s;
	s << 100000 << '\n';
	for (auto i = 0; i < 100000; i++) {
		s << i << ' ' << 100000 - i << '\n';
	}
	size_t N;
	//cin >> N;
	s >> N;
	size_t num, position;
	list<int> l;
	//map<int, list<int>::iterator> nums;
	unordered_map<int, list<int>::iterator> nums;
	for (auto i = 0; i < N; i++) {
		//cin >> num >> position;
		s >> num >> position;
		list<int>::iterator it;
		if (nums.count(position) == 0) {
			l.push_back(num);
			it = prev(l.end());
		} else {
			//auto it = find(l.begin(), l.end(), position);
			it = l.insert(nums[position], num);
		}
		nums[num] = it;
	}
	for (auto it = l.begin(); it != l.end(); it++) {
		cout << *it << endl;
	}
}
