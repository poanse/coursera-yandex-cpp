#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

class BusStops {
public:
	void Add(const set<string>& stops) {
		if (!mapping.count(stops)) {
			mapping[stops] = current_number;
			cout << "New bus " << current_number++ << endl;
		} else {
			cout << "Already exists for " << mapping[stops] << endl;
		}
	}
private:
	map<set<string>, int> mapping;
	int current_number = 1;
};

int main() {
	BusStops busstops;
	int N, K;
	cin >> N;
	for (auto i = 0; i < N; i++) {
		cin >> K;
		set<string> stops;
		string stop;
		for (auto j = 0; j < K; j++) {
			cin >> stop;
			stops.insert(stop);
		}
		busstops.Add(stops);
	}
}
