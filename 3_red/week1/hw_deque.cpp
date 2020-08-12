#include "hw_deque.h"
#include "test_runner.h"

void Test1 (){
	Deque<int> d;
	d.PushBack(1);
	ASSERT_EQUAL(d.Front(), 1);
	ASSERT_EQUAL(d.Back(), 1);
	ASSERT_EQUAL(d.Size(), 1);
	ASSERT_EQUAL(d.Empty(), 0);
	d.PushFront(2);
	ASSERT_EQUAL(d.Front(), 2);
	ASSERT_EQUAL(d.Back(), 1);
	ASSERT_EQUAL(d.Size(), 2);
	ASSERT_EQUAL(d.Empty(), 0);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, Test1);
}
