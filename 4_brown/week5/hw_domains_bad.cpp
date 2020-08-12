#include <algorithm>
#include <iostream>
#include <string>
//#include <string_view>
#include <vector>
#include <unordered_set>
using namespace std;

vector<string> GetDomains(const string& str, char sep = '.') {
	vector<string> output;
	output.push_back({begin(str), end(str)});
	auto it = find(begin(str), end(str), sep);
	while (it != end(str)) {
		output.push_back({++it, end(str)});
		it = find(it, end(str), sep);
	}
	return output;
}

bool IsSubstring(const string& substr, const string& str);

class DomainManager {
private:
	unordered_set<string> domains;
public:
	void Add(string domain) {
		domains.insert(move(domain));
	}

	bool IsBad(const string& str) {
		for (const auto& domain : GetDomains(str)) {
			if (domains.count(domain)) {
				return true;
			}
		}
		return false;
	}
};

int main() {
	DomainManager dm;
  size_t count;
	string domain;
	cin >> count;
  for (size_t i = 0; i < count; ++i) {
		cin >> domain;
		dm.Add(move(domain));
  }
  cin >> count;
  for (size_t i = 0; i < count; ++i) {
		cin >> domain;
		if (dm.IsBad(domain)) {
			cout << "Bad\n";
		} else {
			cout << "Good\n";
		}
  }
}
