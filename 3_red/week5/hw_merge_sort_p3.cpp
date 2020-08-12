#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
//#include <iostream>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2) {
		return;
	}
	vector<typename RandomIt::value_type> v(
			make_move_iterator(range_begin), 
			make_move_iterator(range_end)
	);
	auto it = v.begin() + v.size() / 3;
	auto it2 = v.end() - v.size() / 3;
	MergeSort(v.begin(), it);
	MergeSort(it, it2);
	MergeSort(it2, v.end());
	vector<typename RandomIt::value_type> v2;
	merge(
			make_move_iterator(v.begin()), 
			make_move_iterator(it), 
			make_move_iterator(it), 
			make_move_iterator(it2), 
			back_inserter(v2)
	);
	merge(
			make_move_iterator(v2.begin()), 
			make_move_iterator(v2.end()), 
			make_move_iterator(it2), 
			make_move_iterator(v.end()), 
			range_begin
	);
}


int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
	MergeSort(v.begin(), v.end());
	for (auto x : v) {
		cout << x << ' ';
	}
	cout << endl;

}
