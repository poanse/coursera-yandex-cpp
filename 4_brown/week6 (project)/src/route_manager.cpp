//#include "route_manager.h"
#include "requests.h"
#include <string>
#include <unordered_map>

using namespace std;

// Implementation

const Route::Info* RouteManager::AddRoute(Route::InfoPtr route_info) {
	if (nullptr == route_info) {
		throw invalid_argument("Route is null");
	}
	string bus = route_info->bus;
	// add buses to stop
	for (const auto& stop : route_info->stops) {
		stop_to_buses[stop].insert(bus);
	}

	routes[bus] = make_unique<Route>(move(route_info));
	return routes[bus]->info.get();
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

Route::StatsPtr RouteManager::GetBusInfo(string bus) {
	if (0 == routes.count(bus)) {
		return nullptr;
	}
	auto& route = routes[bus];
	if (nullptr == route->stats) {
		route->CalculateStats(&stops, this);
	}
	return route->stats;
};

GetStopResponsePtr RouteManager::GetStopInfo(std::string stop) {
	auto it = stop_to_buses.find(stop);
	bool found = (it != stop_to_buses.end());
	set<string> buses;
	if (found) {
		buses = it->second;
	}
	return make_unique<GetStopResponse>(stop, found, move(buses));
	//return stop_to_buses[stop];
}

ResponsePtr RouteManager::ProcessAddRequest(AddRequestPtr req) {
	req->Process(this);
	return {};
}

ResponsePtr RouteManager::ProcessGetRequest(GetRequestPtr req) {
	return req->Process(this);
}

