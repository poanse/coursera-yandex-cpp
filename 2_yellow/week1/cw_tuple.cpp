#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <set>
#include <map>
using namespace std;

class Cities {
	public:
		tuple<bool, string>FindCountry(
				const string& city) const {
			if (city_to_country.count(city)) {
				return {true, city_to_country.at(city)};
			} else if (ambiguous_cities.count(city)) {
				return {false, "Ambiguous"};
			} else {
				return {false, "Not exists"};
			}
		}
	private:
		map<string, string> city_to_country;
		set<string> ambiguous_cities;
};

int main() {
	//auto t = make_tuple(7, "C++", true);
	tuple t{7, "C++", true};
	pair p(7, "C++");
	cout << get<1>(t) << endl;
	cout << p.first << " " << p.second << endl;

	// map is a collection of pairs
	Cities cities;
	/*
	bool success;
	string message;
	tie(success, message) = cities.FindCountry("Volgograd");
	*/
	auto [success, message] = cities.FindCountry("Volgograd"); 
	cout << success << " " << message << endl;
}

