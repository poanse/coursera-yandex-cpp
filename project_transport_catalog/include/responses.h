#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>

#include "json.h"
#include "route.h"
#include "distances.h"
#include "router_wrapper.h"

using Id = int;
using Buses = std::set<std::string>;

class Response {
protected:
	Id id;
public:
	Response(Id id_) : id(id_) {}
	virtual Json::Node GetJson() const = 0;
	virtual ~Response() = default;
};

class GetBusResponse : public Response {
	Route::StatsPtr stats;
	std::string bus;
public:
	GetBusResponse(Route::StatsPtr stats_, std::string bus_, Id);
	~GetBusResponse() override = default;
	Json::Node GetJson() const override;
};

class GetStopResponse : public Response {
	Buses buses;
	std::string stop;
	bool found;
public:
	GetStopResponse(std::string, bool, Buses, Id);
	~GetStopResponse() override = default;
	Json::Node GetJson() const override;
};

class GetRouteResponse : public Response {
	std::optional<std::vector<RouterWrapper::RouteStep>> steps;
	double bus_wait_time;
public:
	GetRouteResponse(std::optional<std::vector<RouterWrapper::RouteStep>> steps_, Id id_, double bus_wt) 
		: Response(id_)
		, steps(steps_)
		, bus_wait_time(bus_wt)	
	{
	}
	~GetRouteResponse() override = default;
	Json::Node GetJson() const override;
};

using ResponsePtr = std::unique_ptr<Response>;
using GetBusResponsePtr = std::unique_ptr<GetBusResponse>;
using GetStopResponsePtr = std::unique_ptr<GetStopResponse>;
using GetRouteResponsePtr = std::unique_ptr<GetRouteResponse>;

void ProcessResponsesJson(std::ostream&, const std::vector<ResponsePtr>&);