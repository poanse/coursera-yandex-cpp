#include <iostream>
#include <string>
#include <map>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	  names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  surnames[year] = last_name;
  }
  string GetFullName(int year) {
	  string name = GetName(year, names);
	  string surname = GetName(year, surnames);
	  string output = "";
	  if (name == "n" && surname == "n") {
		  output = "Incognito";
	  } else if (name == "n") {
		  output = surname + " with unknown first name";
	  } else if (surname == "n") {
		  output = name + " with unknown last name";
	  } else {
		  output = name + ' ' + surname;
	  }
	  return output;
  }
private:
  map<int, string> names;
  map<int, string> surnames;
  string GetName(int year, map<int, string>& strings) {
	  auto it = strings.upper_bound(year);
	  if (it != begin(strings)) {
		  return prev(it)->second;
	  }
	  return "n";
	  //string name;
	  //if (strings.count(year)) {
		//name = strings[year];
	  //} else {
		//int max_year = -10000;
		//name = "n";
		//for (auto& kv : strings) {
			//if (kv.first < year && kv.first > max_year) {
				//name = kv.second;
				//max_year = kv.first;
			//}
		//}
	  //}
	  //return name;
  }
};
int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
