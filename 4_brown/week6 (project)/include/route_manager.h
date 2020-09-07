#pragma once
#include "requests.h"
#include "responses.h"
#include "distances.h"
#include "router_wrapper.h"

using Buses = std::set<std::string>;
using Stops = std::unordered_map<std::string, StopPtr>;

class RouteManager {
	friend Route::Stats;
private:
	std::unordered_map<std::string, Buses> stop_to_buses;
	std::unordered_map<std::string, RoutePtr> routes;
	Stops stops;
	Distances distances;
	RoutingSettings routing_settings;
public:
	RouteManager() = default;
	RouteManager(RoutingSettings rs) : routing_settings(rs) {}
	void InitRouter();
	void ProcessAddRequest(AddRequestPtr req);
	ResponsePtr ProcessGetRequest(GetRequestPtr req);
private:
  void ProcessAddRouteRequest(AddRouteRequest* req);
  void ProcessAddStopRequest(AddStopRequest* req);
  GetBusResponsePtr ProcessGetBusRequest(GetBusRequest* req);
  GetStopResponsePtr ProcessGetStopRequest(GetStopRequest* req);
	GetRouteResponsePtr	ProcessGetRouteRequest(GetRouteRequest* req);

	void AddRoute(Route::InfoPtr route_info);
	void AddStop(StopPtr stop, std::unordered_map<StopPair, int>);
	Route::StatsPtr GetBusInfo(std::string bus);
	std::pair<bool, Buses> GetStopInfo(std::string stop);

private:
	std::optional<RouterWrapper> rw = std::nullopt;
};
