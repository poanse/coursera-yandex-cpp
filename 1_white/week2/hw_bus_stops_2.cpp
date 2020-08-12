#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class BusStops {
public:
	void Add(const vector<string>& stops) {
		if (!mapping.count(stops)) {
			mapping[stops] = current_number;
			cout << "New bus " << current_number++ << endl;
		} else {
			cout << "Already exists for " << mapping[stops] << endl;
		}
	}
private:
	map<vector<string>, int> mapping;
	int current_number = 1;
};

int main() {
	BusStops busstops;
	int N, K;
	cin >> N;
	for (auto i = 0; i < N; i++) {
		cin >> K;
		vector<string> stops;
		string stop;
		for (auto j = 0; j < K; j++) {
			cin >> stop;
			stops.push_back(stop);
		}
		busstops.Add(stops);
	}
}
