#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

#include "test_runner.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  char gender;
};

string MostPopularName(vector<Person>& people, char gender) {
	IteratorRange range{
		begin(people),
		partition(begin(people), end(people), [gender](const Person& p) {
			return p.gender == gender;
		})
	};
	if (range.begin() == range.end()) {
		return "";
	} else {
		sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
			return lhs.name < rhs.name;
		});
		const string* most_popular_name = &range.begin()->name;
		int count = 0;
		for (auto i = range.begin(); i != range.end(); ) {
			auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
				return p.name == i->name;
			});
			auto cur_name_count = std::distance(i, same_name_end);
			if (cur_name_count > count) {
				count = cur_name_count;
				most_popular_name = &i->name;
			}
			i = same_name_end;
		}
		return *most_popular_name;
	}
}

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.gender = gender;
  }

  return result;
}

class Data {
public:
	Data(vector<Person> people) {
		for (const auto& person : people) {
			ages.push_back(person.age);
			incomes.push_back(person.income);
		}
		sort(ages.rbegin(), ages.rend());
		sort(incomes.rbegin(), incomes.rend());
		male_name = MostPopularName(people, 'M');
		female_name = MostPopularName(people, 'W');
	}

	int Age(int n) {
		int sum = 0;
		for (int age : ages) {
			if (age < n) {
				break;
			}
			sum += 1;
		}
		return sum;
	}

	int Wealthy(int n) {
		IteratorRange range = Head(incomes, n);
		return accumulate(range.begin(), range.end(), 0);
	}

	string PopularName(char gender) {
		if (gender == 'M') {
			return male_name;
		} else if (gender == 'W') {
			return female_name;
		}
		return "";
	}

private:
	vector<int> ages;
	vector<int> incomes;
	string male_name;
	string female_name;
};


void prog(istream& is, ostream& os){
  vector<Person> people = ReadPeople(is);
	Data data(people);
	map<string, map<int, int>> cache;
  for (string command; is >> command; ) {
    if (command == "AGE") {
      int adult_age;
      is >> adult_age;
			int n_people;
			if (cache["AGE"].count(adult_age)) {
				n_people = cache["AGE"][adult_age];
			} else {
				n_people = data.Age(adult_age);
				cache["AGE"][adult_age] = n_people;
			}

      os << "There are " << n_people
           << " adult people for maturity age " << adult_age << '\n';
					 
    } else if (command == "WEALTHY") {
      int count;
      is >> count;
			int total_income;
			if (cache["WEALTHY"].count(count)) {
				total_income = cache["WEALTHY"][count];
			} else {
				total_income = data.Wealthy(count);
				cache["WEALTHY"][count] = total_income;
			}

			os << "Top-" << count << " people have total income " 
				<< total_income << '\n';

    } else if (command == "POPULAR_NAME") {
      char gender;
      is >> gender;
			if (gender != 'M' && gender != 'W') {
				continue;
			}
			string name = data.PopularName(gender);
			if (name.size()) {
				os << "Most popular name among people of gender " 
					<< gender << " is " << name << '\n';
			} else {
				os << "No people of gender " << gender << '\n';
			}
		}
  }
}

void Test() {
	istringstream instr(
		R"(11
Ivan 25 1000 M
Olga 30 623 W
Sergey 24 825 M
Maria 42 1254 W
Mikhail 15 215 M
Oleg 18 230 M
Denis 53 8965 M
Maxim 37 9050 M
Ivan 47 19050 M
Ivan 17 50 M
Olga 23 550 W
AGE 18
AGE 25
WEALTHY 5
POPULAR_NAME M
POPULAR_NAME W)"
	);

	stringstream outstr;
	prog(instr, outstr);
	string line;
	getline(outstr, line);
	ASSERT_EQUAL(line, "There are 9 adult people for maturity age 18");
	getline(outstr, line);
	ASSERT_EQUAL(line, "There are 6 adult people for maturity age 25");
	getline(outstr, line);
	ASSERT_EQUAL(line, "Top-5 people have total income 39319");
	getline(outstr, line);
	ASSERT_EQUAL(line, "Most popular name among people of gender M is Ivan");
	getline(outstr, line);
	ASSERT_EQUAL(line, "Most popular name among people of gender W is Olga");
}

int main() {
	//TestRunner tr;
	//RUN_TEST(tr, Test);
	prog(cin, cout);
}
