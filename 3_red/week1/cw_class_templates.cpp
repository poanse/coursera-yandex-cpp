#include <iostream>
#include <vector>
#include <set>
#include <deque>
using namespace std;

struct PairOfStringAndInt {
	string first;
	int second;
};

struct PairOfBoolAndChar {
	bool first;
	char second;
};

template <typename T, typename U>
struct Pair {
	T first;
	U second;
};

template <typename Iterator>
class IteratorRange {
private:
	Iterator first, last;
public:
	IteratorRange(Iterator f, Iterator l)
		: first(f)
	  	, last(l) {
	}
	Iterator begin() const {
		return first;
	}
	Iterator end() const {
		return last;
	}
};

template <typename Container>
//IteratorRange<typename Container::iterator> 
auto Head(Container& v, size_t top) {
	return IteratorRange{
		v.begin(), 
		next(v.begin(), min(top, v.size()))
	};
}

template <typename T>
size_t RangeSize(IteratorRange<T> r){
	return r.end() - r.start();
}

template <typename Iterator>
IteratorRange<Iterator> MakeRange(Iterator begin, Iterator end) {
	return IteratorRange<Iterator>{begin,end};
}

int main() {
	PairOfStringAndInt si;
	si.first = "Hello";
	si.second = 5;

	PairOfStringAndInt bc;
	bc.first = true;
	bc.second = 'z';

	Pair<string, int> si2;
	si2.first = "Hello";
	si2.second = 5;

	vector<int> v = {1,2,3,4,5};
	for (int x : v) {
		cout << x << ' ';
	}
	cout << endl;
	for (int i = 0; i < 3; ++i) {
		cout << v[i] << ' ';
	}
	cout << endl;
	for (int& x : Head(v, 3)) {
		x ++;
	}
	for (int& x : Head(v, 5)) {
		cout << x << ' ';
	}
	cout << endl;

	//IteratorRange<vector<int>::iterator> second_half{
		//v.begin() + v.size()/2, v.end()
	//};
	//auto second_half = MakeRange(
		//v.begin() + v.size()/2, v.end()
	//);
	IteratorRange second_half{
		v.begin() + v.size()/2, 
		v.end()
	};
	for (int& x : second_half) {
		cout << x << ' ';
	}
	cout << endl;

	pair p(5, true);

	set<int> nums = {5,7,12,8,10,5,6,1};
	for (int x : Head(nums, 4)) {
		cout << x << ' ';
	}
	cout << endl;

	deque<int> nums2 = {5,7,12,8,10,5,6,1};
	for (int x : Head(nums2, 4)) {
		cout << x << ' ';
	}
	cout << endl;
}
