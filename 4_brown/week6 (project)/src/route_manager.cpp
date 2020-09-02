//#include "route_manager.h"
#include "requests.h"
#include <string>
#include <unordered_map>

using namespace std;

//class RouteManager {
//private:
	//unordered_map<int, RoutePtr> routes;
	//Stops stops;

	//void AddRoute(Route::InfoPtr route_info);

	//void AddStop(StopPtr stop);

	//Route::StatsPtr GetBusInfo(int bus);

//public:
	//ResponsePtr ProcessAddRequest(AddRequestPtr req);

	//ResponsePtr ProcessGetRequest(GetRequestPtr req);
//};

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

void RouteManager::AddStop(StopPtr stop) {
	if (nullptr == stop) {
		throw invalid_argument("Stop is null");
	}
	string name = stop->name;
	stops[name] = move(stop);
	stop_to_buses[name];
}

Route::StatsPtr RouteManager::GetBusInfo(string bus) {
	if (0 == routes.count(bus)) {
		return nullptr;
	}
	auto& route = routes[bus];
	if (nullptr == route->stats) {
		route->CalculateStats(&stops);
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
	//switch (req->type) {
		//case AddRequest::Type::ADD_STOP:
			//AddStop(move(req->stop));
			//break;
		//case AddRequest::Type::ADD_ROUTE:
			//AddRoute(move(req->route));
			//break;
	//}
	return {};
}

ResponsePtr RouteManager::ProcessGetRequest(GetRequestPtr req) {
	//switch (req->type) {
		//case GetRequest::Type::GET_BUS_INFO:
			//return make_unique<Response>(GetBusInfo(req->bus.value()), move(req));
	//}
	return req->Process(this);
}

