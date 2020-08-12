#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <mutex>
#include <future>
#include <map>
#include <unordered_map>
using namespace std;


template <typename K, typename V>
using container = unordered_map<K, V>;

template <typename K, typename V>
class ConcurrentMap {
private:
	mutable vector<mutex*> mutexes;
	//vector<pair<container<K, V>, mutex>> maps;
	vector<container<K, V>> maps;
	hash<K> hasher;
public:
	template <typename T>
  struct Access {
    T& ref_to_value;
		lock_guard<mutex> lock;
  };

  explicit ConcurrentMap(const size_t bucket_count)
		: mutexes(bucket_count)
		,	maps(bucket_count) {
		for (size_t i = 0; i < bucket_count; i++) {
			container<K, V> m;
			maps[i] = move(m);
			mutex *mut = new mutex;
			mutexes[i] = move(mut);
		}
	}

	size_t GetMapIndex(const K key) const {
		return hasher(key) % maps.size();
	}

	bool Has(const K& key) const {
		return maps[GetMapIndex(key)].count(key);
	}

	Access <const V> At(const K& key) const {
		auto idx = GetMapIndex(key);
		const V *ref;
		{
			lock_guard<mutex> lock(*mutexes[idx]);
			ref = &maps[idx].at(key);
		}
		return {*ref, lock_guard<mutex>(*(mutexes[idx]))};
	}

  Access<V> operator[](const K& key) {
		auto idx = GetMapIndex(key);
		V *ref;
		{
			lock_guard<mutex> lock(*mutexes[idx]);
			ref = &maps[idx][key];
		}
		return {*ref, lock_guard<mutex>(*(mutexes[idx]))};
	}

  container<K, V> BuildOrdinaryMap() const {
		container<K, V> result;
		for (size_t i = 0; i < maps.size(); i++) {
			lock_guard<mutex> lock(*(mutexes[i]));
			result.insert(maps[i].begin(), maps[i].end());
		}
		return result;
	}
};




void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));
    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

void TestStringKey() {
	ConcurrentMap<string, int> m(10);
	m["abc"].ref_to_value = 1;
	AssertEqual(m.At("abc").ref_to_value, 1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
  RUN_TEST(tr, TestStringKey);
}
