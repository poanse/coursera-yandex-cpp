#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

const map<string, QueryType> StrToOpCode{
	{"NEW_BUS", QueryType::NewBus},
	{"BUSES_FOR_STOP", QueryType::BusesForStop},
	{"STOPS_FOR_BUS", QueryType::StopsForBus},
	{"ALL_BUSES", QueryType::AllBuses},
};

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
	q = Query();
	string operation_code;
	int stop_count;
	is >> operation_code;
	if (StrToOpCode.count(operation_code) == 0) {
		return is;
	} 
	q.type = StrToOpCode.at(operation_code);
	switch (q.type) {
		case QueryType::NewBus:
			is >> q.bus;
			is >> stop_count;
			q.stops.resize(stop_count);
			for (auto& stop : q.stops) {
				is >> stop;
			}
			break;
		case QueryType::BusesForStop:
			is >> q.stop;
			break;
		case QueryType::StopsForBus:
			is >> q.bus;
			break;
		case QueryType::AllBuses:
			break;
	}
  return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру
	const vector<string>* buses;
};

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

struct StopsForBusResponse {
  // Наполните полями эту структуру
	string bus;
	const vector<pair<string, const vector<string>*>> stops_n_buses;
};

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

struct AllBusesResponse {
  // Наполните полями эту структуру
	const map<string, vector<string>>* buses_to_stops;
};

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

class BusManager {
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
		buses_to_stops[bus] = stops;
		for (const string& stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
		if (stops_to_buses.count(stop) == 0) {
			return {};
		}
		return {&stops_to_buses.at(stop)};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
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

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
		if (buses_to_stops.empty()) {
			return {};
		}
		return {&buses_to_stops};
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
