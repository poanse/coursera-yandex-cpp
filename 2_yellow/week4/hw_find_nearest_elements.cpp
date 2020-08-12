#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
    	const set<int>& numbers,
		int border) {
	if (numbers.size() == 0) {
		return end(numbers);
	}
	auto lower = numbers.lower_bound(border);
	auto upper = numbers.upper_bound(border);
	if (upper == end(numbers)){ 
		return prev(upper);
	} else if (upper == begin(numbers)) {
		return upper;
	} else if (lower != upper) {
		return lower;
	}
	auto dif1 = border - *prev(lower);
	auto dif2 = *upper - border;
	if (dif1 <= dif2) {
		return prev(lower);
	}
	return upper;
}
	
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
