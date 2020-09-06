#include <string>
#include <iostream>
#include <iomanip>
#include "requests.h"

using namespace std;



AddStopRequest::AddStopRequest(AddRequest::Type type_, StopPtr ptr, std::unordered_map<StopPair, int> dist)
	:	AddRequest(type_)
	, stop(std::move(ptr))
	, distances(std::move(dist))
{
}

AddRequest::Type GetAddRequestCode(const string& type) {
	if (type == "Bus") {
		return AddRequest::Type::ADD_ROUTE;
	} else if (type == "Stop") {
		return AddRequest::Type::ADD_STOP;
	} else {
		throw invalid_argument("");
	}
}

GetRequest::Type GetGetRequestCode(const string& type) {
	if (type == "Bus") {
		return GetRequest::Type::GET_BUS_INFO;
	} else if (type == "Stop") {
		return GetRequest::Type::GET_STOP_INFO;
	} else {
		throw invalid_argument("");
	}
}

AddRouteRequestPtr ReadAddRouteRequest(istream& is) {
	string bus;
	is >> ws;
	while (is.peek() != ':') {
		bus += is.get();
	}
	is.ignore(2);
	string stops;
	getline(is, stops);
	return make_unique<AddRouteRequest>(
		AddRequest::Type::ADD_ROUTE, 
		Route::Parser(bus, stops)
	);
}

AddStopRequestPtr ReadAddStopRequest(istream& is) {
	string name;
	is >> ws;
	getline(is, name, ':');
	is.ignore(1);
	double latitude, longitude;
	is >> latitude;
	is.ignore(1);
	is >> longitude;
	string stop_dists;
	getline(is, stop_dists);
	stringstream sd(stop_dists);
	std::unordered_map<StopPair, int> distances;
	while (sd) {
		sd.ignore(1);
		int dist = -1;
		sd >> dist;
		sd.ignore(5); //"m to "
		string stop;
		while (sd.peek() != ',' && sd.peek() != '\n' && sd) {
			stop += sd.get();
		}
		if (dist != -1 && stop != "") {
			//cerr << "name: \"" << name << "\" stop: \"" << stop << "\" dist: " << dist << '\n';
			distances[StopPair(name, move(stop))] = dist;
		}
	}
	return make_unique<AddStopRequest>(
			AddRequest::Type::ADD_STOP, 
		  make_unique<Stop>(name, latitude, longitude),
			move(distances)
	);
}

AddRequestPtr ReadAddRequest(istream& is) {
	string command;
	is >> command;
	if (command == "Bus") {
		try {
			return ReadAddRouteRequest(is);
		} catch (exception& e) {
			cerr << "Failed to read request: " + command + ": "+ e.what() << endl;
		}
	} else if (command == "Stop") {
		try {
			return ReadAddStopRequest(is);
		} catch (exception& e) {
			cerr << "Failed to read request: " + command + ": "+ e.what() << endl;
		}
	} else {
		throw invalid_argument("Request reading failed");
	}
	return nullptr;
}


GetRequestPtr ReadGetRequest(istream& is) {
	string command;
	is >> command;
	if (command == "Bus") {
		string bus;
		is >> ws;
		while (is.peek() != ':' && is.peek() != EOF && is.peek() != '\n') {
			bus += is.get();
		}
		return make_unique<GetBusRequest>(GetRequest::Type::GET_BUS_INFO, bus);
	} else if (command == "Stop") {
		string stop;
		is >> ws;
		while (is.peek() != ':' && is.peek() != EOF && is.peek() != '\n') {
			stop += is.get();
		}
		return make_unique<GetStopRequest>(GetRequest::Type::GET_STOP_INFO, stop);
	}
	return nullptr;
}

ostream& operator<< (ostream& os, AddRequest::Type type) {
	os << static_cast<int>(type);
	return os;
}
ostream& operator<< (ostream& os, GetRequest::Type type) {
	os << static_cast<int>(type);
	return os;
}