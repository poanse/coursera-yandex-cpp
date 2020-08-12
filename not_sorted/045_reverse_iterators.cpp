#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
	for (auto it = range_begin;
			it != range_end; ++it) {
		cout << *it << ' ';
	}
	cout << endl;
}

int main() {
	vector<string> langs = {
		"Python", "C++", "C", "Java", "C#"
	};
	PrintRange(rbegin(langs), rend(langs));
	cout << *rbegin(langs) << endl;

	auto it = find_if(rbegin(langs), rend(langs),
		[](const string& langs) {
			return langs[0] == 'C';
		}
	);
	cout << *it << endl;

	auto it2 = partition(begin(langs), end(langs),
		[](const string& lang) {
			return lang[0] == 'C';
		}
	);
	PrintRange(begin(langs), it2);

	vector<string> c_langs(langs.size());
	auto it3 = copy_if(begin(langs), end(langs), begin(c_langs),
		[](const string& lang) {
			return lang[0] == 'C';
		}
	);
	PrintRange(begin(c_langs), it3);

	set<int> a = {1, 8, 3};
	set<int> b = {3, 6, 8};
	vector<int> v(a.size());
	auto it4 = set_intersection(begin(a), end(a), begin(b), end(b), begin(v));
	PrintRange(begin(v), it4);

	// inserter and back_inserter
	vector<string> c_langs2;
	copy_if(begin(langs), end(langs), back_inserter(c_langs2),
		[](const string& lang) {
			return lang[0] == 'C';
		}
	);
	PrintRange(begin(c_langs2), end(c_langs2));

	a = {1, 3, 8};
	b = {3, 7, 8};
	set<int> res;
	set_intersection(begin(a), end(a),
			begin(b), end(b), inserter(res, end(res)));
	PrintRange(begin(res), end(res));
	
	auto it5 = a.find(1);
	PrintRange(next(it5), end(a));

}
