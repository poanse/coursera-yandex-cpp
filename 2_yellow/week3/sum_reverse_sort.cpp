#include "sum_reverse_sort.h"
#include <algorithm>
#include <string>
#include <vector>
//#include <iostream>
using namespace std;

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	size_t l = s.length();
	char tmp;
	for (size_t i = 0; i < l / 2; i++) {
		tmp = s[i];
		s[i] = s[l - 1 - i];
		s[l - 1 - i] = tmp;
	}
	return s;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}

//int main() {
	//int x = 5, y = 3;
	//string str = "abcde";
	//vector<int> vec = {3, 2, 1};
	//cout << Sum(x,y) << endl;
	//cout << Reverse(str) << endl;
	//for (auto x : vec) {
		//cout << x << ' ';
	//}
//}
