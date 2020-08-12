#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>

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
		//cerr << "putting..." << endl;
		if (1 == id_index.count(record.id)) {
			return false;
		}
		data.push_front(record);
		auto it = data.begin();
		id_index[record.id] = it;
		//Record* p = &data.front();
		//id_index[record.id] = p;
		Record* p = &(*it);
		timestamp_index.insert({record.timestamp, p});
		karma_index.insert({record.karma, p});
		user_index.insert({record.user, p});
		return true;
	}

  const Record* GetById(const string& id) const 
	{
		if (0 == id_index.count(id)) {
			return nullptr;
		}
		return &(*id_index.at(id));
	}

  bool Erase(const string& id)
	{
		if (0 == id_index.count(id)) {
			return false;
		}
		//auto it = id_index.find(id);
		//Record* p = it->second;
		//id_index.erase(it);
		auto it = id_index.find(id);
		auto data_it = it->second;
		Record* p = &(*data_it);
		id_index.erase(it);

		auto time_it = timestamp_index.lower_bound(p->timestamp);
		while (id != time_it->second->id) {
			time_it++;
		}
		timestamp_index.erase(time_it);

		auto karma_it = karma_index.lower_bound(p->karma);
		while (id != karma_it->second->id) {
			karma_it++;
		}
		karma_index.erase(karma_it);

		auto user_it = user_index.lower_bound(p->user);
		while (id != user_it->second->id) {
			user_it++;
		}
		user_index.erase(user_it);
		
		//data.remove_if(
				//[p](Record& record){ 
					//return record.id == p->id;
				//}
		//);
		data.erase(data_it);
		return true;
	}

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const
	{
		auto low_it = timestamp_index.lower_bound(low);
		auto high_it = timestamp_index.upper_bound(high);
		while (low_it != high_it && callback(*low_it->second)) {
			low_it++;
		}
	}

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const
	{
		//cerr << "rangebykarma..." << endl;
		auto low_it = karma_index.lower_bound(low);
		auto high_it = karma_index.upper_bound(high);
		while (low_it != high_it && callback(*low_it->second)) {
			low_it++;
		}
	}

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const
	{
		auto low_it = user_index.lower_bound(user);
		auto high_it = user_index.upper_bound(user);
		while (low_it != high_it && callback(*low_it->second)) {
			low_it++;
		}
	}
private:
	list<Record> data;
	//unordered_map<string, Record*> id_index; // map by id
	unordered_map<string, list<Record>::iterator> id_index; // map by id
	multimap<int, Record*> timestamp_index;//multimap by timestamp
	multimap<int, Record*> karma_index;//multimap by karma
	multimap<string, Record*> user_index;//multimap by user
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
