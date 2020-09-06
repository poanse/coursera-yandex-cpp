#pragma once
#include "requests.h"
#include "responses.h"

struct RoutingSettings {
	int bus_wait_time; // minutes
	double bus_velocity; // km per hour
}

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
	void ProcessAddRequest(AddRequestPtr req);
	ResponsePtr ProcessGetRequest(GetRequestPtr req);

private:
  void ProcessAddRouteRequest(AddRouteRequest* req);
  void ProcessAddStopRequest(AddStopRequest* req);
  GetBusResponsePtr ProcessGetBusRequest(GetBusRequest* req);
  GetStopResponsePtr ProcessGetStopRequest(GetStopRequest* req);

	void AddRoute(Route::InfoPtr route_info);
	void AddStop(StopPtr stop, Distances);
	Route::StatsPtr GetBusInfo(std::string bus);
	std::pair<bool, Buses> GetStopInfo(std::string stop);
};
