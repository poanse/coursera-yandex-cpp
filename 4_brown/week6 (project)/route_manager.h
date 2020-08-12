#pragma once
#include <unordered_map>
#include "route.h"
#include "requests.h"

class RouteManager {
private:
	std::unordered_map<std::string, RoutePtr> routes;
	Stops stops;

	const Route::Info* AddRoute(Route::InfoPtr route_info);

	void AddStop(StopPtr stop);

	Route::StatsPtr GetBusInfo(std::string bus);

public:
	ResponsePtr ProcessAddRequest(AddRequestPtr req);

	ResponsePtr ProcessGetRequest(GetRequestPtr req);
};

