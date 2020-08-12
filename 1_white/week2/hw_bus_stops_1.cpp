#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

template<typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
	if (v.size() == 0) {
		return os;
	}
	if (v.size() == 1) {
		os << v[0];
		return os;
	}
	auto it = v.begin();
	while (it != prev(v.end())) {
		os << *it << ' ';
		it++;
	}
	os << *it;
	return os;
}


class BusStops {
public:
	void NewBus(const string& bus, const vector<string>& stops) {
		bus_to_stop[bus] = stops;
		for (auto stop : stops) {
			stop_to_bus[stop].push_back(bus);
		}
	}
	void BusesForStop(const string& stop) const {
		if (!stop_to_bus.count(stop)) {
			cout << "No stop" << endl;
			return;
		}
		cout << stop_to_bus.at(stop) << endl;
	}
	void StopsForBus(const string& bus) const {
		if (!bus_to_stop.count(bus)) {
			cout << "No bus" << endl;
			return;
		}
		for (auto stop : bus_to_stop.at(bus)) {
			cout << "Stop " << stop << ":";
			if (stop_to_bus.at(stop).size() < 2) {
				cout << ' ' << "no interchange";
			} else {
				for (const auto& other_bus : stop_to_bus.at(stop)) {
					if (other_bus != bus) {
						cout << ' ' << other_bus;
					}
				}
			}
			cout << endl;
		}
	}
	void AllBuses() {
		if (bus_to_stop.size() == 0) {
			cout << "No buses" << endl;
			return;
		}
		for (auto& [bus, stops] : bus_to_stop) {
			cout << "Bus " << bus << ':';
			for (auto stop : stops) {
				cout << ' ' << stop;
			}
			cout << endl;
		}
		//cout << endl;
	}
private:
	map<string, vector<string>> bus_to_stop;
	map<string, vector<string>> stop_to_bus;
};

int main() {
	BusStops busstops;
	int Q, N;
	cin >> Q;
	string command, bus, stop;
	for (auto i = 0; i < Q; i++) {
		cin >> command;
		if (command == "ALL_BUSES") {
			busstops.AllBuses();
		} else if (command == "NEW_BUS") {
			cin >> bus >> N;
			vector<string> stops;
			for (;N > 0; N--) {
				cin >> stop;
				stops.push_back(stop);
			}
			busstops.NewBus(bus, stops);
		} else if (command == "BUSES_FOR_STOP") {
			cin >> stop;
			busstops.BusesForStop(stop);
		} else if (command == "STOPS_FOR_BUS") {
			cin >> bus;
			busstops.StopsForBus(bus);
		}
	}
}
