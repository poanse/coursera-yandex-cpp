#pragma once
#include "requests.h"
#include "responses.h"

class RouteManager {
	friend Route::Stats;
private:
	std::unordered_map<std::string, Buses> stop_to_buses;
	std::unordered_map<std::string, RoutePtr> routes;
	Stops stops;
	Distances distances;

public:
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
