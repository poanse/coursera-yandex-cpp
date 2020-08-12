#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


struct Mycomp {
	Mycomp(const string& prefix) {
		size = prefix.size();
	}
	bool operator() (const string& str, const string& prefix) {
		return str.substr(0, size) < prefix.substr(0,size);
	}
private:
	size_t size;
};
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) 
{
	for (auto x : prefix) {
		if (x < 'A' || x > 'z' || (x > 'Z' && x < 'a')) {
			throw invalid_argument("");
		}
	}
	Mycomp mycomp(prefix);
	return make_pair(lower_bound(range_begin, range_end, prefix, mycomp),
		upper_bound(range_begin, range_end, prefix, mycomp));
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix_) 
{
	string prefix = "";
	prefix += prefix_;
	Mycomp mycomp(prefix);
	return make_pair(lower_bound(range_begin, range_end, prefix, mycomp),
		upper_bound(range_begin, range_end, prefix, mycomp));
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  return 0;
}
