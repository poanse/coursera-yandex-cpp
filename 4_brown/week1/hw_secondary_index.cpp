#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>
#include <list>
#include <deque>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record) 
	{
		if (1 == id_index.count(record.id)) {
			return false;
		}
		data.push_front(record);
		auto data_it = data.begin();

		auto time_it = timestamp_index.insert({record.timestamp, data_it});
		auto karma_it = karma_index.insert({record.karma, data_it});
		auto user_it = user_index.insert({data_it->user, data_it});

		id_index.insert({data_it->id, {data_it, user_it, karma_it, time_it}});
		return true;
	}

  const Record* GetById(const string& id) const 
	{
		auto id_it = id_index.find(id);
		if (id_index.end() == id_it) {
			return nullptr;
		}
		return &(*id_it->second.data_it);
	}

  bool Erase(const string& id)
	{
		auto id_it = id_index.find(id);
		if (id_index.end() == id_it) {
			return false;
		}

		const auto& recit = id_it->second;
		timestamp_index.erase(recit.timestamp_index_it);
		karma_index.erase(recit.karma_index_it);
		user_index.erase(recit.user_index_it);
		auto data_it = recit.data_it;
		id_index.erase(id_it);
		data.erase(data_it);
		return true;
	}

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const
	{
		auto it = timestamp_index.lower_bound(low);
		while ((it != timestamp_index.end()) && (it->first <= high) && 
				callback(*it->second)) {
			it++;
		}
	}

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const
	{
		auto it = karma_index.lower_bound(low);
		while ((it != karma_index.end()) && (it->first <= high) && 
				callback(*it->second)) {
			it++;
		}
	}

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const
	{
		auto range = user_index.equal_range(user);
		for (auto it = range.first; 
				 it != range.second && callback(*it->second); 
				 it++) 
		{
		}
	}
private:
	using DataIter = list<Record>::iterator;
	struct RecIt {
		list<Record>::iterator data_it;
		multimap<string_view, DataIter>::iterator user_index_it;
		multimap<int, DataIter>::iterator karma_index_it;
		multimap<int, DataIter>::iterator timestamp_index_it;
	};

	list<Record> data;
	unordered_map<string_view, RecIt> id_index; // map by id
	multimap<string_view, DataIter> user_index;//multimap by user
	multimap<int, DataIter> timestamp_index;//multimap by timestamp
	multimap<int, DataIter> karma_index;//multimap by karma
};


void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
