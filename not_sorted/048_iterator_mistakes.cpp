#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	vector<int> s {1,2,7};
	vector<int> t {2,7};
	//end(s) - begin(s); // no operator-
	//partial_sort(begin(s), end(s),end(s),end(s));
	//remove(begin(s), end(s),0);
	sort(begin(s), rend(s));
}
