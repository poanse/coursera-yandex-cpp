#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

using Priority = int;
template <typename T>
class PriorityCollection {
public:
  using Id = int;/* тип, используемый для идентификаторов */;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
		T *p = new T;
		*p = move(object);
		mapping[next_id] = {0, p};
		return next_id++;
	}

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
		while (range_begin != range_end) {
			*ids_begin++ = next_id;
			Add(move(*range_begin++));
		}
	}

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
		return mapping.count(id);
	}

  // Получить объект по идентификатору
  const T& Get(Id id) const {
		return *mapping.at(id).second;
	}

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
		//cout << "Before " << mapping[id].first 
			//<< " for " << id << endl;
		mapping[id].first += 1;
		//cout << "After " << mapping[id].first
			//<< " for " << id << endl;
	}

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
		pair<Priority, T*> tmp = max_element(
				rbegin(mapping),
				rend(mapping),
				[](const auto& lhs, const auto& rhs){
					return lhs.second.first < rhs.second.first;
				}
		)->second;
		return {*(tmp.second), tmp.first};
	}

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
		auto it = max_element(
					rbegin(mapping),
					rend(mapping),
					[](const auto& lhs, const auto& rhs){
						return lhs.second.first < rhs.second.first;
					}
		);
		pair<Priority, T*> tmp = move(it->second);
		mapping.erase(it->first);
		return {move(*(tmp.second)), tmp.first};
	}

private:
  // Приватные поля и методы
	map<Id, pair<Priority, T*>> mapping;
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
