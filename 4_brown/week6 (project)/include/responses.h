#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>

#include "route.h"

struct Response {
	int id;
	Response(int id_) : id(id_) {}
	virtual void Process(std::ostream& os) const {};
	virtual void ProcessJson(std::ostream& os) const {};
	virtual ~Response() = default;
};

struct GetBusResponse : Response {
	Route::StatsPtr stats;
	std::string bus;

	GetBusResponse(Route::StatsPtr stats_, std::string bus_, int id_ = 0) 
		: Response(id_)
		, stats(std::move(stats_))
		, bus(std::move(bus_))
	{
	}

	void Process(std::ostream& os) const override;
	void ProcessJson(std::ostream& os) const override;
	~GetBusResponse() override = default;
};

struct GetStopResponse : Response {
	std::set<std::string> buses;
	std::string stop;
	bool found;

	GetStopResponse(std::string stop_, bool found_, 
			std::set<std::string> buses_ = {}, int id_ = 0) 
		: Response(id_)
		, stop(std::move(stop_))
		, found(found_)
	{
		if (found) {
			buses = std::move(buses_);
		}
	}

	void Process(std::ostream& os) const override;
	void ProcessJson(std::ostream& os) const override;
	~GetStopResponse() override = default;
};

using ResponsePtr = std::unique_ptr<Response>;
using GetBusResponsePtr = std::unique_ptr<GetBusResponse>;
using GetStopResponsePtr = std::unique_ptr<GetStopResponse>;

void ProcessResponse(std::ostream& os, const Response* resp);
void ProcessResponseJson(std::ostream& os, const Response* resp);
void ProcessResponsesJson(std::ostream& os, const std::vector<ResponsePtr>& responses);

