#include "route_manager.h"
#include <string>

using namespace std;

void RouteManager::ProcessAddRequest(AddRequestPtr req) {
	switch (req->type) {
		case AddRequest::Type::ADD_ROUTE:
			ProcessAddRouteRequest(dynamic_cast<AddRouteRequest*>(req.get()));
			break;
		case AddRequest::Type::ADD_STOP:
			ProcessAddStopRequest(dynamic_cast<AddStopRequest*>(req.get()));
			break;
	}
}

void RouteManager::ProcessAddRouteRequest(AddRouteRequest* req) {
	AddRoute(move(req->route));
}
void RouteManager::AddRoute(Route::InfoPtr route_info) {
	if (nullptr == route_info) {
		throw invalid_argument("Route is null");
	}
	const string& bus = route_info->bus;
	// add buses to stop
	for (const auto& stop : route_info->stops) {
		stop_to_buses[stop].insert(bus);
	}
	routes[bus] = make_unique<Route>(move(route_info));
}

void RouteManager::ProcessAddStopRequest(AddStopRequest* req) {
	AddStop(move(req->stop), move(req->distances));
}
void RouteManager::AddStop(StopPtr stop, std::unordered_map<StopPair, int> new_distances) {
	if (nullptr == stop) {
		throw invalid_argument("Stop is null");
	}
	string name = stop->name;
	stops[name] = move(stop);
	stop_to_buses[name];
	distances.insert( make_move_iterator(begin(new_distances)), 
										make_move_iterator(end(new_distances)) );
}


ResponsePtr RouteManager::ProcessGetRequest(GetRequestPtr req) {
	switch (req->type) {
		case GetRequest::Type::GET_BUS_INFO:
			return ProcessGetBusRequest(dynamic_cast<GetBusRequest*>(req.get()));
		case GetRequest::Type::GET_STOP_INFO:
			return ProcessGetStopRequest(dynamic_cast<GetStopRequest*>(req.get()));
		case GetRequest::Type::GET_ROUTE_INFO:
			return ProcessGetRouteRequest(dynamic_cast<GetRouteRequest*>(req.get()));
	}
	return {};
}

GetBusResponsePtr RouteManager::ProcessGetBusRequest(GetBusRequest* req) {
	Route::StatsPtr stats = GetBusInfo(req->bus);
	return make_unique<GetBusResponse>(move(stats), move(req->bus), req->id);
}
Route::StatsPtr RouteManager::GetBusInfo(string bus) {
	if (0 == routes.count(bus)) {
		return nullptr;
	}
	auto& route = routes[bus];
	if (nullptr == route->stats) {
		route->CalculateStats(&stops, distances);
	}
	return route->stats;
};

GetStopResponsePtr RouteManager::ProcessGetStopRequest(GetStopRequest* req) {
	auto [found, buses] = GetStopInfo(req->stop);
	return make_unique<GetStopResponse>(move(req->stop), found, move(buses), req->id);
}
pair<bool, set<string>> RouteManager::GetStopInfo(std::string stop) {
	auto it = stop_to_buses.find(stop);
	bool found = (it != stop_to_buses.end());
	set<string> buses;
	if (found) {
		buses = it->second;
	}
	return {found, move(buses)};
}

GetRouteResponsePtr	RouteManager::ProcessGetRouteRequest(GetRouteRequest* req) {
	optional<vector<RouteStep>> steps = rw.value().GetRoute(req->from, req->to);
	return make_unique<GetRouteResponse>(move(steps), req->id);
}


void RouteManager::InitRouter() {
	// rw = RouterWrapper(stops, routes, [this](const string& stop1, const string& stop2) -> double { return this->GetEdgeWeight(stop1, stop2);});
	rw.emplace(stops, routes, distances, routing_settings);
}