#include "json.h"
#include "requests.h"
#include <iostream>
#include <sstream>
using namespace std;

//template <typename K, typename V>
//ostream& operator<<(ostream& os, unordered_map<K,V> m) {
	//os << "{ ";
	//for (auto it = m.begin(); it != m.end(); it++) {
		//os << it->first << ": " << it->second;
	//}
	//os << " }";
	//return os;
//}
//ostream& operator<<(ostream& os, StopPair p) {
	//os << p.stops.first << " - " << p.stops.second;
	//return os;
//}

AddStopRequestPtr GetAddStopRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	string name = m.at("name").AsString();
	double latitude;
	auto& lat_node = m.at("latitude");
	if (holds_alternative<double>(lat_node)) {
		latitude = lat_node.AsDouble();
	} else if (holds_alternative<int>(lat_node)) {
		latitude = lat_node.AsInt();
	} else {
		throw invalid_argument("");
	}
	double longitude;
	auto& long_node = m.at("longitude");
	if (holds_alternative<double>(long_node)) {
		longitude = long_node.AsDouble();
	} else if (holds_alternative<int>(long_node)) {
		longitude = long_node.AsInt();
	} else {
		throw invalid_argument("");
	}
	StopPtr stop_ptr = make_unique<Stop>(name, latitude, longitude);

	map<string, Json::Node> distances_map = m["road_distances"].AsMap();
	std::unordered_map<StopPair, int> dist;
	for (auto it = distances_map.begin(); it != distances_map.end(); it++) {
		dist[StopPair(name, it->first)] = it->second.AsInt();
	}
	return make_unique<AddStopRequest>(AddRequest::Type::ADD_STOP, 
			move(stop_ptr), move(dist) );
}

AddRouteRequestPtr GetAddRouteRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	string bus = m.at("name").AsString();
	bool is_circular = m.at("is_roundtrip").AsBool();
	std::list<std::string> stops;
	for (auto stop_node : m.at("stops").AsArray()) {
		stops.push_back(stop_node.AsString());
	}
	if (is_circular) {
		stops.pop_back();
	}
	Route::InfoPtr route_ptr = make_unique<Route::Info>(bus, is_circular, stops);
	return make_unique<AddRouteRequest>( AddRequest::Type::ADD_ROUTE, move(route_ptr) );
}

AddRequestPtr GetAddRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	string type = m["type"].AsString();
	AddRequest::Type add_request_code = GetAddRequestCode(type);
	switch (add_request_code) {
		case AddRequest::Type::ADD_ROUTE:
			return GetAddRouteRequestFromJson(m);
		case AddRequest::Type::ADD_STOP:
			return GetAddStopRequestFromJson(m);
		default:
			throw invalid_argument("");
	}
}


//GetBusRequestPtr GetGetBusRequestFromJson(const Json::Node& node);
//GetStopRequestPtr GetGetStopRequestFromJson(const Json::Node& node);

GetRequestPtr GetGetRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	string type = m.at("type").AsString();
	string name = m.at("name").AsString();
	int id = m.at("id").AsInt();
	GetRequest::Type get_request_code = GetGetRequestCode(type);
	switch (get_request_code) {
		case GetRequest::Type::GET_BUS_INFO:
			return make_unique<GetBusRequest>(get_request_code, name, id);
		case GetRequest::Type::GET_STOP_INFO:
			return make_unique<GetStopRequest>(get_request_code, name, id);
		default:
			throw invalid_argument("");
	}
}