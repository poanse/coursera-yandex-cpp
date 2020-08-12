#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
	if (r.buses == nullptr) {
		os << "No stop";
	} else {
		for (const auto& bus : *r.buses) {
			os << bus << " ";
		}
	}
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
	if (r.stops_n_buses.empty()) {
		os << "No bus";
		return os;
	}
	for (auto it = r.stops_n_buses.begin(); 
			it != r.stops_n_buses.end();
			it++) 
	{
		const auto& stop = it->first;
		const auto& buses = it->second;
		os << "Stop " << stop << ": ";
		if (buses->size() == 1) {
			os << "no interchange";
		} else {
			for (const auto& other_bus : *buses) {
				if (r.bus != other_bus) {
					os << other_bus << " ";
				}
			}
		}
		if (it != prev(r.stops_n_buses.end())){
			os << '\n';
		}
	}
  return os;
}


ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
	if (r.buses_to_stops == nullptr || r.buses_to_stops->empty()) {
		os << "No buses";
	} else {
		for (auto it = r.buses_to_stops->begin(); 
				it != r.buses_to_stops->end();
				it++) 
		{
			const auto& bus_item = *it;
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			if (it != prev(r.buses_to_stops->end())) {
				os << endl;
			}
		}
	}
  return os;
}
