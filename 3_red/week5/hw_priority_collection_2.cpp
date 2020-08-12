#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

using namespace std;

using Priority = int;
constexpr Priority DEFAULT_PRIORITY = 0;

template <typename T>
class PriorityCollection {
public:
  using Id = int;/* тип, используемый для идентификаторов */;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
		//cerr << "Add started" << endl;
		T *ptr = new T(move(object));
		auto uptr = unique_ptr<T>(ptr);
		item_by_id[next_id] = {DEFAULT_PRIORITY, move(uptr)};
		id_by_priority[DEFAULT_PRIORITY].push_back(next_id);
		//cerr << "Add finished" << endl;
		return next_id++;
	}

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
		while (range_begin != range_end) {
			*ids_begin++ = Add(move(*range_begin++));
		}
	}

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
		return item_by_id.count(id);
	}

  // Получить объект по идентификатору
  const T& Get(Id id) const {
		return *item_by_id.at(id).second;
	}

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
		//cerr << "Promote started" << endl;
		auto& p = item_by_id[id];
		//cerr << "Priority = " << p.first << endl;
		auto& old_list = id_by_priority[p.first++];
		auto& new_list = id_by_priority[p.first];
		new_list.splice(new_list.end(), old_list, 
				find(old_list.begin(), old_list.end(), id));
		//cerr << "Promote finished" << endl;
		//cerr << "Priority = " << p.first << endl;
	}

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
		auto tmp = *prev(id_by_priority.cend());
		auto priority = tmp.first;
		auto id = *max_element(tmp.second.begin(), tmp.second.end());
		return {*item_by_id.at(id).second, priority};
	}

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
		//cerr << "PopMax started" << endl;
		auto& tmp = *id_by_priority.rbegin();
		auto priority = tmp.first;
		auto id_it = max_element(tmp.second.begin(), tmp.second.end());
		auto id = *id_it;
		//cerr << "PopMax started clearing id_by_priority" << endl;
		if (tmp.second.size() > 1) {
			tmp.second.erase(id_it);
		} else {
			id_by_priority.erase(priority);
		}
		//cerr << "PopMax cleared id_by_priority" << endl;
		auto it = item_by_id.find(id);
		auto pair = make_pair(move(*(it->second.second)), it->second.first);
		if (item_by_id.size() > 1) {
			item_by_id.erase(it);
		} else {
			item_by_id.clear();
		}
		//cerr << "PopMax finished" << endl;
		return pair;
	}
private:
  // Приватные поля и методы
	map<Priority, list<Id>> id_by_priority;
	unordered_map<Id, pair<Priority, unique_ptr<T>>> item_by_id;
	Id next_id = 0;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");
  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
