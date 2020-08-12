#include <iostream>
#include <algorithm>
using namespace std;

//enum class Gender {
  //FEMALE,
  //MALE
//};

//struct Person {
  //int age;  // возраст
  //Gender gender;  // пол
  //bool is_employed;  // имеет ли работу
//};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
//template <typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  //if (range_begin == range_end) {
    //return 0;
  //}
  //vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  //auto middle = begin(range_copy) + range_copy.size() / 2;
  //nth_element(
      //begin(range_copy), middle, end(range_copy),
      //[](const Person& lhs, const Person& rhs) {
        //return lhs.age < rhs.age;
      //}
  //);
  //return middle->age;
//}

void PrintStats(vector<Person> persons) {
	auto start = std::begin(persons);
	auto end = std::end(persons);
	auto it_female = partition(start, end, 
			[](const Person& lhs){
				return lhs.gender==Gender::MALE;
			}
	);
	auto it_unemployed_male = partition(start, it_female, 
			[](const Person& lhs){
				return lhs.is_employed;
			}
	);
	auto it_unemployed_female = partition(it_female, end,
			[](const Person& lhs){
				return lhs.is_employed;
			}
	);
	cout << "Median age = " << ComputeMedianAge(start, end) << '\n';
	cout << "Median age for females = " 
		<< ComputeMedianAge(it_female, end) << '\n';
	cout << "Median age for males = " 
		<< ComputeMedianAge(start, it_female) << '\n';
	cout << "Median age for employed females = " 
		<< ComputeMedianAge(it_female, it_unemployed_female) << '\n';
	cout << "Median age for unemployed females = " 
		<< ComputeMedianAge(it_unemployed_female, end) << '\n';
	cout << "Median age for employed males = " 
		<< ComputeMedianAge(start, it_unemployed_male) << '\n';
	cout << "Median age for unemployed males = " 
		<< ComputeMedianAge(it_unemployed_male, it_female) << endl;
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
