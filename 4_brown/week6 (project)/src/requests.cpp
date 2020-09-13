#include <string>
#include <iostream>
#include <iomanip>
#include "requests.h"

using namespace std;

AddStopRequest::AddStopRequest(StopPtr ptr, std::unordered_map<StopPair, int> dist)
	:	AddRequest(AddRequest::Type::ADD_STOP)
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
		throw invalid_argument("Failed to determine AddRequest code");
	}
}

GetRequest::Type GetGetRequestCode(const string& type) {
	if (type == "Bus") {
		return GetRequest::Type::GET_BUS_INFO;
	} else if (type == "Stop") {
		return GetRequest::Type::GET_STOP_INFO;
	} else if (type == "Route") {
		return GetRequest::Type::GET_ROUTE_INFO;
	} else {
		throw invalid_argument("Failed to determine GetRequest code");
	}
}

ostream& operator<< (ostream& os, AddRequest::Type type) {
	os << static_cast<int>(type);
	return os;
}
ostream& operator<< (ostream& os, GetRequest::Type type) {
	os << static_cast<int>(type);
	return os;
}