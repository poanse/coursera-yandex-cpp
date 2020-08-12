#include "responses.h"
#include "bus_manager.h"
//#include <string>
//#include <vector>
//#include <map>

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
	// Реализуйте этот метод
	buses_to_stops[bus] = stops;
	for (const string& stop : stops) {
		stops_to_buses[stop].push_back(bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	// Реализуйте этот метод
	if (stops_to_buses.count(stop) == 0) {
		return {};
	}
	return {&stops_to_buses.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	// Реализуйте этот метод
	if (buses_to_stops.count(bus) == 0) {
		return {bus, {}};
	}
	vector<pair<string, const vector<string>*>> stops_n_buses;
	for (const auto& stop : buses_to_stops.at(bus)) {
		stops_n_buses.push_back({stop, &stops_to_buses.at(stop)});
	}	
	return {bus, move(stops_n_buses)};
}

AllBusesResponse BusManager::GetAllBuses() const {
	// Реализуйте этот метод
	if (buses_to_stops.empty()) {
		return {};
	}
	return {&buses_to_stops};
}
