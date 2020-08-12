#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
set<Char<String>> StringToSet(const String& str) {
	set<Char<String>> chars;
	for (auto& ch : str) {
		chars.insert(ch);
	}
	return chars;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  // Напишите реализацию функции,
  // использовав не более 1 копирования каждого символа
	map<set<Char<String>>, Group<String>> mapping;
	set<Char<String>> set_tmp;
	for (auto& str : strings) {
		// convert string into a set of characters
		set_tmp = StringToSet(str);
		// copy string into corresponding group
		mapping[move(set_tmp)].push_back(move(str));
	}
	vector<Group<String>> result(mapping.size());
	// convert map to vector
	int i = 0;
	for (auto& [key,value] : mapping) {
		result[i++] = move(value);
	}
	//cout << strings << endl;
	//cout << result << endl;
	return result;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
	vector<string> strings;
	for (auto i = 0; i < 100000; i++) {
		strings.push_back("abcdeabcde");
	}
	{
		LOG_DURATION("100000, 10");
		GroupHeavyStrings(strings);
	}
	strings.clear();
	for (auto i = 0; i < 100000; i++) {
		strings.push_back("abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcde");
	}
	{
		LOG_DURATION("100000, 40");
		GroupHeavyStrings(strings);
	}
  return 0;
}
