#include "profile.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <future>

using namespace std;

int SumToVectors(const vector<int>& one, 
		const vector<int>& two) {
	future<int> f = async([&one] {return accumulate(begin(one), end(one), 0);});
	int result = accumulate(begin(two), end(two), 0);
	return result +	f.get();
}

int SumToVectors2(const vector<int>& one, 
		const vector<int>& two) {
	return accumulate(begin(two), end(two), 0) +
		accumulate(begin(one), end(one), 0);
}

const int N_ELEMENTS = 10000000;

int main() {
	vector<int> v1;
	vector<int> v2;
	for (auto i = 0; i < N_ELEMENTS; i++) {
		v1.push_back(i);
		v2.push_back(i);
	}
	{
		LOG_DURATION("no async");
		SumToVectors2(v1, v2);
	}
	{
		LOG_DURATION("async");
		SumToVectors(v1, v2);
	}
}
