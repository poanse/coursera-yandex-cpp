#include <iostream>
#include <string>
#include <map>
#include <vector>

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
	string GetFullNameWithHistory(int year) {
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
  map<int, string> names;
  map<int, string> surnames;
  string GetName(int year, map<int, string>& strings) {
	  auto it = strings.upper_bound(year);
	  if (it != begin(strings)) {
		  return prev(it)->second;
	  }
	  return "n";
  }
	vector<string> GetNameWithHistory(int year, map<int, string>& strings) {
		vector<string> hist;
		for (auto it = rbegin(strings); it != rend(strings); it++) {
			if (it->first <= year) {
				hist.push_back(it->second);
			}
		}
		return hist;
	}
	string OutputHistory(vector<string> hist) {
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
  Person person;
  
  //person.ChangeFirstName(1965, "Polina");
  //person.ChangeLastName(1967, "Sergeeva");
  //for (int year : {1900, 1965, 1990}) {
    //cout << person.GetFullName(year) << endl;
  //}
  
  //person.ChangeFirstName(1970, "Appolinaria");
  //for (int year : {1969, 1970}) {
    //cout << person.GetFullName(year) << endl;
  //}
  
  //person.ChangeLastName(1968, "Volkova");
  //for (int year : {1969, 1970}) {
    //cout << person.GetFullName(year) << endl;
  //}
	//
	//
  //person.ChangeFirstName(1900, "Eugene");
  //person.ChangeLastName(1900, "Sokolov");
  //person.ChangeLastName(1910, "Sokolov");
  //person.ChangeFirstName(1920, "Evgeny");
  //person.ChangeLastName(1930, "Sokolov");
  //cout << person.GetFullNameWithHistory(1940) << endl; 
	//
	//
	person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  return 0;
}
