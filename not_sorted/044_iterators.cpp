#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
using namespace std;

struct Lang {
	string name;
	int age;
};

ostream& operator<<(ostream& s, Lang& lang) {
	s << lang.name << ' ' << lang.age;
	return s;
}
template <typename T, typename P>
ostream& operator<<(ostream& s, pair<T, P> lang) {
	s << lang.first << ' ' << lang.second;
	return s;
}

template <typename It>
void PrintRange(It range_begin, It range_end) {
	for (auto it = range_begin;
			it != range_end; ++it) {
		cout << *it << ' ';
	}
	cout << endl;
}

int main() {
	//vector<Lang> langs = {
		//{"Python", 26},
		//{"C++", 34},
		//{"C", 45}, 
		//{"Java",22},
		//{"C#", 17}
	//};
	//auto result = find_if(
		//langs.begin(), 
		//langs.end(),
		//[](const Lang& lang) {
			//return lang.name[0] == 'D';
		//}
	//);
	//if (result == end(langs)) {
		//cout << "not found" << endl;
	//} else {
		//cout << (*result).age << endl;
		//cout << result->age << endl;
	//}
	//cout << begin(langs)->name << " "
		//<< begin(langs)->age << endl;
	
	//PrintRange(begin(langs), end(langs));

	//string lang = langs[1].name;
	//auto it = begin(lang);
	//cout << *it;
	//++it;
	//cout << *it;
	
	//string& res = *result;
	//res = "D++";
	//cout << res << endl;
	
	//set<string> langs = {
		//"Python", "C++", "C", "Java", "C#"
	//};
	//auto it = langs.find("C++");
	//PrintRange(begin(langs), it);
	//PrintRange(it, end(langs));
	
	//map<string, int> langs = {
		//{"Python", 26},
		//{"C++", 34},
		//{"C", 45}, 
		//{"Java",22},
		//{"C#", 17}
	//};
	//auto it = langs.find("C++");
	//PrintRange(begin(langs), it);
	//PrintRange(it, end(langs));
	//
	vector<string> langs = {
		"Python", "C++", "C", "Java", "C#"
	};
	//auto it = find(begin(langs), end(langs), "C++");
	//langs.erase(it,end(langs));
	//langs.insert(begin(langs), "C++");
	//PrintRange(begin(langs), end(langs));
	auto it = remove_if(begin(langs), end(langs),
		[](const string& lang) {
			return lang[0] == 'C';
		}
	);
	langs.erase(it, end(langs));
	PrintRange(begin(langs), end(langs));

	langs = {"Python", "C++", "C++","C","C++"};
	auto iter = unique(begin(langs), end(langs));
	langs.erase(iter, end(langs));
	PrintRange(begin(langs), end(langs));

	langs = {"Python", "C++", "C++","C","C++"};
	sort(begin(langs), end(langs));
	iter = unique(begin(langs), end(langs));
	langs.erase(iter, end(langs));
	PrintRange(begin(langs), end(langs));

	langs = {"Python", "C++", "C++","C","C++"};
	auto iter2 = min_element(begin(langs), end(langs));
	cout << *iter2 << endl;
	
	langs = {"Python", "C++", "C++","C","C++"};
	auto iter3 = minmax_element(begin(langs), end(langs));
	cout << *iter3.first << ' ' << *iter3.second << endl;

	set<string> setlangs = {"Python", "C++", "C++","C","C++"};
	cout << all_of(begin(setlangs), end(setlangs),
			[](const string& lang) {
				return lang[0] >= 'A' && lang[0] <= 'Z';
			}
	);

}
