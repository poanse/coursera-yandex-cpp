#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& name, const string& surname, int year)
		: year_of_birth_(year)
	{
		names.insert({year, name});
		surnames.insert({year, surname});
	}

  void ChangeFirstName(int year, const string& first_name) {
		if (year >= year_of_birth_) {
			names[year] = first_name;
		}
  }
  void ChangeLastName(int year, const string& last_name) {
		if (year >= year_of_birth_) {
			surnames[year] = last_name;
		}
  }
  string GetFullName(int year) const {
		if (year < year_of_birth_) {
			return "No person";
		}
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
	string GetFullNameWithHistory(int year) const {
		if (year < year_of_birth_) {
			return "No person";
		}
		auto name_history = GetNameWithHistory(year, names);
		auto surname_history = GetNameWithHistory(year, surnames);
		auto name = OutputHistory(name_history);
		auto surname = OutputHistory(surname_history);
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
	int year_of_birth_;
  map<int, string> names;
  map<int, string> surnames;
  string GetName(int year, const map<int, string>& strings) const {
	  auto it = strings.upper_bound(year);
	  if (it != begin(strings)) {
		  return prev(it)->second;
	  }
	  return "n";
  }
	vector<string> GetNameWithHistory(int year, const map<int, 
			string>& strings) const {
		vector<string> hist;
		for (auto it = rbegin(strings); it != rend(strings); it++) {
			if (it->first <= year) {
				hist.push_back(it->second);
			}
		}
		return hist;
	}
	string OutputHistory(vector<string> hist) const {
		if (hist.size() == 0) {
			return "n";
		} else if (hist.size() == 1) {
			return hist[0];
		} else {
			string output;
			output += hist[0];
			int i = 1;
			while (hist[i] == hist[0] && i < hist.size()) {
				i++;
			}
			if (i < hist.size()) {
				output += " (";
				while (i < hist.size()) {
					output += hist[i] + ", ";
					i++;
				}
				output = output.substr(0, output.length()-2);
				output += ")";
			}
			return output;
		}
	}
};
int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
	return 0;
}
