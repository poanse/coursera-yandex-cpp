#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
		T* p = TryAllocate();
		if (p) {
			return p;
		}
		p = new T;
		allocated.insert(p);
		return p;
	}

  T* TryAllocate() {
		if (deallocated.empty()) {
			return nullptr;
		}
		T* p = deallocated.front();
		deallocated.pop();
		allocated.insert(p);
		return p;
	}

  void Deallocate(T* object) {
		auto it = allocated.find(object);
			//find(allocated.begin(), allocated.end(), object);
		if (it != allocated.end()) {
			allocated.erase(it);
			deallocated.push(object);
			return;
		}
		throw invalid_argument("123");
	}

  ~ObjectPool() {
		for (T* p : allocated) {
			delete p;
		}
		while (!deallocated.empty()) {
			T *p = deallocated.front();
			delete p;
			deallocated.pop();
		}
	}

private:
  // Добавьте сюда поля
	set<T*> allocated;
	queue<T*> deallocated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
