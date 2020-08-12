#include "requests.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

AddRequest::AddRequest(AddRequest::Type type_, Route::InfoPtr ptr)
	:	type(type_)
	, route(move(ptr))
{
}
AddRequest::AddRequest(AddRequest::Type type_, StopPtr ptr)
	:	type(type_)
	, stop(move(ptr))
{
}

GetRequest::GetRequest(GetRequest::Type type_, string b)
	: type(type_)
	, bus(b)
{
}

Response::Response(Route::StatsPtr stats_) 
	: stats(stats_) 
{
}

Response::Response(Route::StatsPtr stats_, GetRequestPtr getreq_) 
	: stats(stats_)
	, getreq(move(getreq_))
{
	if (stats.value() == nullptr) {
		stats.reset();
	}
}

//Response::Response(string msg_) 
	//: msg(move(msg_) 
//{
//}

void ProcessResponse(ostream& os, const Response* resp) {
	if (nullptr == resp) {
		throw invalid_argument("No response given");
	}
	// TBD: check request code with switch
	os << setprecision(6);
	os << "Bus " << resp->getreq.value()->bus.value() << ": ";
	if (resp->stats.has_value()) {
		const auto& stats = *resp->stats.value();
		os << stats.n_stops << " stops on route, " 
			 << stats.n_unique_stops << " unique stops, "
			 << stats.route_length * 1000 << " route length\n";
	} else if (!resp->stats.has_value()) {
		os << "not found\n";
	}
}

AddRequestPtr ReadAddRequest(istream& is) {
	string command;
	is >> command;
	if (command == "Bus") {
		string bus;
		is >> ws;
		while (is.peek() != ':') {
			bus += is.get();
		}
		is.ignore(2);
		string stops;
		getline(is, stops);
		try {
			return make_unique<AddRequest>(AddRequest::Type::ADD_ROUTE, 
				Route::Parser(bus, stops));
		} catch (exception& e) {
			cerr << "Failed to read request: " + command + ' ' + bus + ": "+ e.what() << endl;
		}
	} else if (command == "Stop") {
		is.ignore(1);
		string name;
		getline(is, name, ':');
		is.ignore(1);
		double latitude, longitude;
		is >> latitude;
		is.ignore(1);
		is >> longitude;
		try {
			return make_unique<AddRequest>(AddRequest::Type::ADD_STOP, 
				make_unique<Stop>(name, latitude, longitude));
		} catch (exception& e) {
			cerr << "Failed to read request: " + command + ' ' + name + ": "+ e.what() << endl;
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
		//int bus;
		//is >> bus;
		return make_unique<GetRequest>(GetRequest::Type::GET_BUS_INFO, bus);
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

