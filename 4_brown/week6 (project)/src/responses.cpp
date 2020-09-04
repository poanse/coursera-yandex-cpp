#include "responses.h"
#include <iomanip>
#include <iostream>

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


void ProcessResponse(std::ostream& os, const Response* resp) {
	if (nullptr == resp) {
		throw std::invalid_argument("No response given");
	}
	resp->Process(os);
}

void ProcessResponseJson(std::ostream& os, const Response* resp) {
	if (nullptr == resp) {
		throw std::invalid_argument("No response given");
	}
	resp->ProcessJson(os);
}

void ProcessResponsesJson(std::ostream& os, const std::vector<ResponsePtr>& responses) {
	os << '[' << '\n';
	if (!responses.empty()) {
		auto it = responses.begin();
		for (; it != prev(responses.end()); it++) {
			ProcessResponseJson(os, it->get());
			os << ',' << '\n';
		}
		ProcessResponseJson(os, it->get());
		os << '\n';
	}
	os << ']' << '\n';
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
