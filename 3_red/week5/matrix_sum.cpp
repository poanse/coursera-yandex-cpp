#include "test_runner.h"
#include "profile.h"
#include <vector>
#include <future>
#include <numeric>
using namespace std;


int64_t VectorSum(const vector<int>& vec) {
	return accumulate(begin(vec), end(vec), (int64_t)0);
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  // Реализуйте эту функцию
	const size_t size = matrix.size();
	const size_t n_threads = 4;
	vector<future<void>> futures;
	vector<int64_t> results(n_threads);
	for (auto n = 0; n < n_threads; n++) {
		futures.push_back(async([&matrix, n, size, &results]{
			int64_t tmp = 0;
			for (auto i = n * size / n_threads; 
					i < (n + 1) * size / n_threads;
					i++) {
				tmp += VectorSum(matrix[i]);
			}
			results[n] = move(tmp);
		}));
	}
	for (auto& f : futures) {
		f.get();
	}
	return accumulate(begin(results), end(results), (int64_t)0);
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
	const int SIZE = 9000;
	vector<vector<int>> matrix(SIZE);
	for (auto j = 0; j < SIZE; j++){
		vector<int> tmp(SIZE);
		for (auto i = 0; i < SIZE; i++) {
			tmp[i] = i+j;
		}
		matrix[j] = move(tmp);
	}
	{
		LOG_DURATION("Size = 9000")
		cout << CalculateMatrixSum(matrix) << endl;
	}
}
