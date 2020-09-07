#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>

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
	virtual void Process(std::ostream& os) const {};
	virtual void ProcessJson(std::ostream& os) const {};
	virtual ~Response() = default;
};

class GetBusResponse : public Response {
	Route::StatsPtr stats;
	std::string bus;
public:
	GetBusResponse(Route::StatsPtr stats_, std::string bus_, Id);
	~GetBusResponse() override = default;
	void Process(std::ostream& os) const override;
	void ProcessJson(std::ostream& os) const override;
};

class GetStopResponse : public Response {
	Buses buses;
	std::string stop;
	bool found;
public:
	GetStopResponse(std::string, bool, Buses, Id);
	~GetStopResponse() override = default;
	void Process(std::ostream& os) const override;
	void ProcessJson(std::ostream& os) const override;
};

class GetRouteResponse : public Response {
	std::optional<std::vector<RouteStep>> steps;
public:
	GetRouteResponse(std::optional<std::vector<RouteStep>> steps_, Id id_) : Response(id_), steps(steps_)	{}
	~GetRouteResponse() override = default;
	void Process(std::ostream& os) const override {}
	void ProcessJson(std::ostream& os) const override;
};

using ResponsePtr = std::unique_ptr<Response>;
using GetBusResponsePtr = std::unique_ptr<GetBusResponse>;
using GetStopResponsePtr = std::unique_ptr<GetStopResponse>;
using GetRouteResponsePtr = std::unique_ptr<GetRouteResponse>;

void ProcessResponsesJson(std::ostream&, const std::vector<ResponsePtr>&);