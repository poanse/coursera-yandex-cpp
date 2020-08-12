#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

void TestCopyAssignment() {
  SimpleVector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  SimpleVector<int> dest;
  ASSERT_EQUAL(dest.Size(), 0u);

  dest = numbers;
  ASSERT_EQUAL(dest.Size(), numbers.Size());
  ASSERT(dest.Capacity() >= dest.Size());
  ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));

	SimpleVector<int> dest2(numbers);
  ASSERT_EQUAL(dest2.Size(), numbers.Size());
  ASSERT(dest2.Capacity() >= dest2.Size());
  ASSERT(equal(dest2.begin(), dest2.end(), numbers.begin()));

	auto dest3 = (dest2 = numbers);
  ASSERT_EQUAL(dest3.Size(), numbers.Size());
  ASSERT(dest3.Capacity() >= dest3.Size());
  ASSERT(equal(dest3.begin(), dest3.end(), numbers.begin()));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCopyAssignment);
}
