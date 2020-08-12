#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
/*
enum class Lang {
	DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
*/
auto GetTie(const Region& region) {
	return tie(region.std_name, region.parent_std_name,
			region.names, region.population);
}

bool operator==(const Region& lhs, const Region& rhs) {
	return (GetTie(lhs) == GetTie(rhs));
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
	int max_value = 0;
	map<int, int> counts;
	for (int i = 0; i < regions.size(); ++i) {
		int duplicate = 0;
		for (auto& [key,value] : counts) {
			if (regions[i] == regions[key]) {
				value += 1;
				duplicate = 1;
			}
		}
		if (duplicate == 0) {
			counts[i] = 1;
		}
	}
	// return maximum value in counts
	for (auto& [key,value] : counts) {
		if (max_value < value) {
			max_value = value;
		}
	}
	return max_value;
};
/*
int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;
  
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;
  
  return 0;
}
*/
