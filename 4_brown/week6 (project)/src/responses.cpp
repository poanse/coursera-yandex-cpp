#include "responses.h"
#include <iomanip>
#include <iostream>
#include <map>

//template<typename T>
//std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
	//auto it = s.begin();
	//for (; it != prev(s.end()); it++) {
		//os << *it << ' ';
	//}
	//os << *it;
	//return os;
//}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
	os << "[";
	if (!s.empty()) {
		auto it = s.begin();
		for (; it != prev(s.end()); it++) {
			os << '"' << *it << '"' << ',' << '\n';
		}
		os << '"' << *it << '"';
	}
	os << "]";
	return os;
}

void ProcessResponsesJson(std::ostream& os, const std::vector<ResponsePtr>& responses) {
	os << '[' << '\n';
	if (!responses.empty()) {
		auto it = responses.begin();
		for (; it != prev(responses.end()); it++) {
			(*it)->ProcessJson(os);
			os << ',' << '\n';
		}
		(*it)->ProcessJson(os);
		os << '\n';
	}
	os << ']' << '\n';
}
   
GetBusResponse::GetBusResponse(Route::StatsPtr stats_, std::string bus_, int id_ = 0) 
	: Response(id_)
	, stats(std::move(stats_))
	, bus(std::move(bus_))
{
}

GetStopResponse::GetStopResponse(std::string stop_, bool found_, 
			std::set<std::string> buses_ = {}, int id_ = 0)
	: Response(id_)
	, stop(std::move(stop_))
	, found(found_)
{
	if (found) {
		buses = std::move(buses_);
	}
}

void GetBusResponse::Process(std::ostream& os) const {
	os << std::setprecision(7);
	os << "Bus " << bus << ": ";
	if (stats) {
		os << stats->n_stops << " stops on route, " 
			 << stats->n_unique_stops << " unique stops, "
			 << stats->route_length_true << " route length, "
			 << stats->curvature << " curvature" << '\n';
	} else {
		os << "not found\n";
	}
}

void GetStopResponse::Process(std::ostream& os) const {
	os << std::setprecision(6);
	os << "Stop " << stop << ": ";
	if (found) {
		if (buses.size()) {
			os << "buses " << buses << "\n";
		} else {
			os << "no buses\n";
		}
	} else {
		os << "not found\n";
	}
}



void GetBusResponse::ProcessJson(std::ostream& os) const {
	os << std::setprecision(6);
	os << '{' << '\n';
	os  << "\"request_id\": " << id << ',' << '\n';
	if (!stats) {
		os << "\"error_message\": " << "\"not found\"";
	} else {
		os << "\"route_length\": " << stats->route_length_true << ',' << '\n';
		os << "\"curvature\": " << stats->curvature << ',' << '\n';
		os << "\"stop_count\": " << stats->n_stops << ',' << '\n';
		os << "\"unique_stop_count\": " << stats->n_unique_stops;
	}
	os << '\n' << '}';
}

void GetStopResponse::ProcessJson(std::ostream& os) const {
	os << std::setprecision(6);
	os << '{' << '\n';
	os  << "\"request_id\": " << id << ',' << '\n';
	if (found) {
		os  << "\"buses\": " << buses << '\n';
	} else {
		os << "\"error_message\": " << "\"not found\"\n";
	}
	os << '}';
}

std::ostream& operator<< (std::ostream& os, const std::pair<std::string,std::string>& p) {
	if (p.first == "time" || p.first == "span_count") {
		os << '\"' << p.first << '\"' << ": " << std::atof(p.second.c_str());
	} else {
		os << '\"' << p.first << "\": \"" << p.second << "\"";
	}
	return os;
}

std::ostream& operator<< (std::ostream& os, const std::map<std::string,std::string>& m) {
	os << '{' << '\n';
	auto it = m.begin();
	for (; it != prev(m.end()); it++) {
		os << *it << ',' << '\n';
	}
	os << *it  << '\n';
	os << '}';
	return os;
}

void GetRouteResponse::ProcessJson(std::ostream& os) const {
	using Item = std::map<std::string, std::string>;
	std::vector<Item> items;
	Item item;
	double total_weight = 0;
	if (steps) {
		// output for debugging
		for (auto& step : steps.value()) {
			total_weight += step.weight;

			item["type"] = "Wait";
			item["time"] = std::to_string(bus_wait_time);
			item["stop_name"] = step.stop_from;
			items.push_back(move(item));

			item["type"] = "Bus";
			item["span_count"] = std::to_string(step.stop_count);
			item["time"] = std::to_string(step.weight - bus_wait_time);
			item["bus"] = step.bus;
			items.push_back(move(item));
			// std::cerr << "Waiting for " << bus_wait_time;
			// std::cerr << '\n';
			// std::cerr << step.stop_from << ' ';
			// std::cerr << step.stop_to << ' ';
			// std::cerr << step.bus << ' ';
			// std::cerr << step.weight - bus_wait_time << ' ';
			// std::cerr << step.stop_count << ' ';
			// std::cerr << '\n';
		}
	}
	// 	if (!steps.value().empty()) {
	// 		for (auto it = steps.value().begin(); it!=steps.value().end();it++) {
	// 			if (it->stop_from == it->stop_to) {
	// 				if (it->weight == 0) {
	// 					items.push_back(std::move(item));
	// 				} else {
	// 					item["type"] = "Wait";
	// 					item["time"] = std::to_string(it->weight);
	// 					total_weight += it->weight;
	// 					item["stop_name"] = it->stop_from;
	// 					items.push_back(std::move(item));
	// 					item["bus"] = it->bus;
	// 				}
	// 			} else if (it->bus == item["bus"]) {
	// 				item["type"] = "Bus";
	// 				total_weight += it->weight;
	// 				item["time"] = std::to_string(atof(item["time"].c_str()) + it->weight);
	// 				item["span_count"] = std::to_string(atoi(item["span_count"].c_str()) + 1);
	// 			} else {
	// 				throw std::invalid_argument("Route steps parsing: unexpected branch");
	// 			}
	// 		}
	// 		if (!item.empty()) {
	// 			throw std::invalid_argument("Route steps parsing failed");
	// 		}
	// 	}
	// }

	os << std::setprecision(14);
	os << '{' << '\n';
	os << "\"request_id\": " << id << ',' << '\n';
	if (steps) {
		os << "\"total_time\": " << total_weight << ',' << '\n';
		os << "\"items\": ";
		os << '[' << '\n';
		if (!items.empty()) {
			auto it = items.begin();
			for (; it != prev(items.end()); it++) {
				os << *it << ',' << '\n';
			}
			os << *it << '\n';
		}
		os << ']' << '\n';
	} else {
		os << "\"error_message\": \"not found\"" << '\n';
	}
	os << '}';
}