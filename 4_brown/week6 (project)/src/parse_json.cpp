#include "json.h"
#include "requests.h"
#include "route_manager.h"

#include <iostream>
#include <sstream>

using namespace std;

double GetDouble(const Json::Node& node) {
	if (holds_alternative<double>(node)) {
		return node.AsDouble();
	} else if (holds_alternative<int>(node)) {
		return node.AsInt();
	} else {
		throw invalid_argument("Failde attempt to get numeric value from json node");
	}
}

int GetInt(const Json::Node& node) {
	if (holds_alternative<double>(node)) {
		return node.AsDouble();
	} else if (holds_alternative<int>(node)) {
		return node.AsInt();
	} else {
		throw invalid_argument("Failde attempt to get numeric value from json node");
	}
}

RoutingSettings GetRoutingSettingsFromJson(const Json::Node& node) {
	if (!holds_alternative<std::map<std::string, Json::Node>>(node)) {
		throw invalid_argument("Problem with parsing routing settings");
	}
	auto m = node.AsMap();
	RoutingSettings rs;
	rs.bus_wait_time = GetInt(m["bus_wait_time"]);
	rs.bus_velocity = GetDouble(m["bus_velocity"]);
	return rs;
}

AddStopRequestPtr GetAddStopRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	string name = m.at("name").AsString();
	double latitude = GetDouble(m.at("latitude"));
	double longitude = GetDouble(m.at("longitude"));
	StopPtr stop_ptr = make_unique<Stop>(name, latitude, longitude);

	map<string, Json::Node> distances_map = m["road_distances"].AsMap();
	std::unordered_map<StopPair, int> dist;
	for (auto it = distances_map.begin(); it != distances_map.end(); it++) {
		dist[StopPair(name, it->first)] = it->second.AsInt();
	}
	return make_unique<AddStopRequest>(move(stop_ptr), move(dist));
}

AddRouteRequestPtr GetAddRouteRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	string bus = m.at("name").AsString();
	bool is_circular = m.at("is_roundtrip").AsBool();
	std::list<std::string> stops;
	for (auto stop_node : m.at("stops").AsArray()) {
		stops.push_back(stop_node.AsString());
	}
	// if (is_circular) {
	// 	stops.pop_back();
	// }
	Route::InfoPtr route_ptr = make_unique<Route::Info>(bus, is_circular, stops);
	return make_unique<AddRouteRequest>(move(route_ptr) );
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

GetRequestPtr GetGetRequestFromJson(const Json::Node& node) {
	map<string, Json::Node> m = node.AsMap();
	int id = m.at("id").AsInt();
	string type = m.at("type").AsString();
	GetRequest::Type request_code = GetGetRequestCode(type);
	switch (request_code) {
		case GetRequest::Type::GET_BUS_INFO:
			return make_unique<GetBusRequest>(id, m.at("name").AsString());
		case GetRequest::Type::GET_STOP_INFO:
			return make_unique<GetStopRequest>(id, m.at("name").AsString());
		case GetRequest::Type::GET_ROUTE_INFO:
			return make_unique<GetRouteRequest>(id, m.at("from").AsString(), m.at("to").AsString());
		default:
			throw invalid_argument("");
	}
}