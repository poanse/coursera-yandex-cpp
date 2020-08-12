#include "profile.h"
#include <vector>
#include <tuple>
#include <array>

using namespace std;

vector<int> BuildVector(int i) {
	return {i, i+1, i+2, i+3, i+4};
}

tuple<int,int,int,int,int> BuildTuple(int i) {
	return {i, i+1, i+2, i+3, i+4};
}

array<int, 5> BuildArray(int i) {
	return {i, i+1, i+2, i+3, i+4};
}

const int COUNT = 10000000;

int main() {
	int tmp = 0;
	{
		LOG_DURATION("vector");
		for (int i = 0; i < COUNT; ++i) {
			auto numbers = BuildVector(i);
			tmp += numbers.size();
		}
	}
	{
		LOG_DURATION("tuple");
		for (int i = 0; i < COUNT; ++i) {
			auto numbers = BuildTuple(i);
			tmp += std::get<0>(numbers);
		}
	}
	{
		LOG_DURATION("array");
		for (int i = 0; i < COUNT; ++i) {
			auto numbers = BuildArray(i);
			tmp += numbers.size();
		}
	}
	return 0;
}
