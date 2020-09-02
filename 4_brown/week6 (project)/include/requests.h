#pragma once
#include <iostream>
#include <iomanip>
#include <optional>
#include <memory>
#include <unordered_map>
#include <set>

#include "route.h"

class AddRequest;
class AddBusRequest;
class AddStopRequest;
class GetRequest;
class GetBusRequest;
class GetStopRequest;

class Response;
class GetBusResponse;
class GetStopResponse;

using AddRequestPtr = std::unique_ptr<AddRequest>;
using AddBusPtr = std::unique_ptr<AddBusRequest>;
using AddStopPtr = std::unique_ptr<AddStopRequest>;

using GetRequestPtr = std::unique_ptr<GetRequest>;
using GetBusRequestPtr = std::unique_ptr<GetBusRequest>;

using ResponsePtr = std::unique_ptr<Response>;
using GetStopResponsePtr = std::unique_ptr<GetStopResponse>;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s);

class RouteManager {
	friend AddBusRequest;
	friend AddStopRequest;
	friend GetBusRequest;
	friend GetStopRequest;
private:
	std::unordered_map<std::string, RoutePtr> routes;
	Stops stops;
	std::unordered_map<std::string, std::set<std::string>> stop_to_buses;

	const Route::Info* AddRoute(Route::InfoPtr route_info);
	void AddStop(StopPtr stop);

	Route::StatsPtr GetBusInfo(std::string bus);
	//std::set<std::string_view> GetStopInfo(std::string stop);
	GetStopResponsePtr GetStopInfo(std::string stop);

public:
	ResponsePtr ProcessAddRequest(AddRequestPtr req);
	ResponsePtr ProcessGetRequest(GetRequestPtr req);
};


struct AddRequest {
	enum class Type {
		ADD_ROUTE, 
		ADD_STOP,
	};
	AddRequest::Type type;
	AddRequest(AddRequest::Type type_) : type(type_) {}
	virtual void Process(RouteManager *rm) = 0;
};

struct AddBusRequest : AddRequest {
	Route::InfoPtr route;

	AddBusRequest(AddRequest::Type type_, Route::InfoPtr ptr)
		:	AddRequest(type_)
		, route(move(ptr))
	{
	}

	void Process(RouteManager* rm) override {
		rm->AddRoute(move(route));
	}

};


struct AddStopRequest : AddRequest {
	StopPtr stop;
	AddStopRequest(AddRequest::Type type_, StopPtr ptr)
		:	AddRequest(type_)
		, stop(move(ptr))
	{
	}

	void Process(RouteManager* rm) override {
		rm->AddStop(move(stop));
	}
};

struct GetRequest {
	enum class Type {
		GET_BUS_INFO,
		GET_STOP_INFO
	};
	GetRequest::Type type;
	GetRequest(GetRequest::Type type_) : type(type_) {}
	virtual ResponsePtr Process(RouteManager* rm) = 0;
};


struct Response {
	virtual void Process(std::ostream& os) const {};
	virtual ~Response() = default;
};

struct GetBusResponse : Response {
	Route::StatsPtr stats;
	std::string bus;

	GetBusResponse(Route::StatsPtr stats_, std::string bus_) 
		: stats(move(stats_))
		, bus(move(bus_))
	{
	}

	void Process(std::ostream& os) const override;
	~GetBusResponse() override = default;
};

struct GetStopResponse : Response {
	std::set<std::string> buses;
	std::string stop;
	bool found;

	GetStopResponse(std::string stop_, bool found_, 
			std::set<std::string> buses_ = {}) 
		: stop(move(stop_))
		, found(found_)
	{
		if (found) {
			buses = move(buses_);
		}
	}

	void Process(std::ostream& os) const override;
	~GetStopResponse() override = default;
};
struct GetBusRequest : GetRequest {
	std::string bus;

	GetBusRequest(GetRequest::Type type_, std::string b)
		: GetRequest(type_)
		, bus(b)
	{
	}

	ResponsePtr Process(RouteManager* rm) override {
		auto *ptr = new GetBusResponse(rm->GetBusInfo(bus), move(bus));
		std::unique_ptr<Response> resp(ptr);
		return resp;
	}
};

struct GetStopRequest : GetRequest {
	std::string stop;

	GetStopRequest(GetRequest::Type type_, std::string s)
		: GetRequest(type_)
		, stop(s)
	{
	}

	ResponsePtr Process(RouteManager* rm) override {
		//auto *ptr = new GetStopResponse(rm->GetStopInfo(stop), move(stop));
		//std::unique_ptr<Response> resp(ptr);
		//return resp;
		return rm->GetStopInfo(stop);
	}
};



void ProcessResponse(std::ostream& os, const Response* resp);

AddRequestPtr ReadAddRequest(std::istream& is);

GetRequestPtr ReadGetRequest(std::istream& is);

std::ostream& operator<< (std::ostream& os, AddRequest::Type type);
std::ostream& operator<< (std::ostream& os, GetRequest::Type type);
