#include <iostream>
#include <vector>
#include <algorithm>
//#include <iostream>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2) {
		return;
	}
	vector<typename RandomIt::value_type> v(range_begin, range_end);
	auto it = v.begin() + v.size() / 2;
	MergeSort(v.begin(), it);
	MergeSort(it, v.end());
	merge(v.begin(), it, it, v.end(), range_begin);
}


int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	MergeSort(v.begin(), v.end());
	for (auto x : v) {
		cout << x << ' ';
	}
	cout << endl;

}
