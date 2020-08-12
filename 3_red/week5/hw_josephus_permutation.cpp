#include "test_runner.h"
#include "profile.h"
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>
#include <array>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool;
  for (auto it = first; it != last; it++) {
		pool.push_back(move(*(it)));
  }
	auto pos = pool.begin();
  while (!pool.empty()) {
		*(first++) = move(*pos);
		pos = pool.erase(pos);
		if (pool.empty()) {
			break;
		}
		if (pos == pool.end()) {
			pos = pool.begin();
		}
		for (auto i = 0; i + 1 < step_size; i++) {
			pos++;
			if (pos == pool.end()) {
				pos = pool.begin();
			}
		}
  }
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
  {
	vector<int> numbers_copy = numbers;
	MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
	ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
	vector<int> numbers_copy = numbers;
	MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
	ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

int main() {
  //vector<int> v = {0,1,2,3,4,5};
  //auto tmp = GetJosephusSequence(v.begin(), v.end(), 3);
  //Permute(v.begin(), v.end(), tmp);
  //cout << v;
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  {
	LOG_DURATION("1,000");
	vector<int> numbers(1000);
	MakeJosephusPermutation(begin(numbers), end(numbers),2);
  }
  {
	LOG_DURATION("100,000");
	vector<int> numbers(100000);
	MakeJosephusPermutation(begin(numbers), end(numbers),200);
  }
  return 0;
}
