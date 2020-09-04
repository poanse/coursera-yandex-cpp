#pragma once
#include <iostream>
#include <iomanip>
#include <optional>
#include <memory>
#include <unordered_map>
#include <set>

#include "stop_pair.h"
#include "route.h"
#include "responses.h"

class AddRequest;
class AddRouteRequest;
class AddStopRequest;
class GetRequest;
class GetBusRequest;
class GetStopRequest;

class Response;
class GetBusResponse;
class GetStopResponse;

using AddRequestPtr = std::unique_ptr<AddRequest>;
using AddRouteRequestPtr = std::unique_ptr<AddRouteRequest>;
using AddStopRequestPtr = std::unique_ptr<AddStopRequest>;

using GetRequestPtr = std::unique_ptr<GetRequest>;
using GetBusRequestPtr = std::unique_ptr<GetBusRequest>;
using GetStopRequestPtr = std::unique_ptr<GetStopRequest>;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s);

class RouteManager {
	friend AddRouteRequest;
	friend AddStopRequest;
	friend GetBusRequest;
	friend GetStopRequest;
	friend Route::Stats;
private:
	std::unordered_map<std::string, std::set<std::string>> stop_to_buses;
	std::unordered_map<std::string, RoutePtr> routes;
	Stops stops;
	std::unordered_map<StopPair, int> distances;

private:
	const Route::Info* AddRoute(Route::InfoPtr route_info);
	void AddStop(StopPtr stop, std::unordered_map<StopPair, int>);

	Route::StatsPtr GetBusInfo(std::string bus);

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
	virtual ~AddRequest() = default;
};

AddRequest::Type GetAddRequestCode(const std::string& type);

struct AddRouteRequest : AddRequest {
	Route::InfoPtr route;

	AddRouteRequest(AddRequest::Type type_, Route::InfoPtr ptr)
		:	AddRequest(type_)
		, route(std::move(ptr))
	{
	}

	void Process(RouteManager* rm) override {
		rm->AddRoute(std::move(route));
	}
};

struct AddStopRequest : AddRequest {
	StopPtr stop;
	std::unordered_map<StopPair, int> distances;
	AddStopRequest(AddRequest::Type type_, StopPtr ptr, std::unordered_map<StopPair, int> dist)
		:	AddRequest(type_)
		, stop(std::move(ptr))
		, distances(std::move(dist))
	{
	}

	void Process(RouteManager* rm) override {
		rm->AddStop(std::move(stop), std::move(distances));
	}
};

struct GetRequest {
	enum class Type {
		GET_BUS_INFO,
		GET_STOP_INFO
	};

	GetRequest::Type type;
	int id;

	GetRequest(GetRequest::Type type_, int id_) 
		: type(type_)
	  , id(id_)
	{
	}
	virtual ResponsePtr Process(RouteManager* rm) = 0;
	virtual ~GetRequest() = default;
};

GetRequest::Type GetGetRequestCode(const std::string& type);

struct GetBusRequest : GetRequest {
	std::string bus;

	GetBusRequest(GetRequest::Type type_, std::string b, int id_ = 0)
		: GetRequest(type_, id_)
		, bus(b)
	{
	}

	ResponsePtr Process(RouteManager* rm) override {
		auto *ptr = new GetBusResponse(rm->GetBusInfo(bus), std::move(bus), id);
		std::unique_ptr<Response> resp(ptr);
		return resp;
	}
};

struct GetStopRequest : GetRequest {
	std::string stop;

	GetStopRequest(GetRequest::Type type_, std::string s, int id_ = 0)
		: GetRequest(type_, id_)
		, stop(s)
	{
	}

	ResponsePtr Process(RouteManager* rm) override {
		auto resp = rm->GetStopInfo(stop);
		resp->id = id;
		return resp;
	}
};

AddRequestPtr ReadAddRequest(std::istream& is);
GetRequestPtr ReadGetRequest(std::istream& is);

std::ostream& operator<< (std::ostream& os, AddRequest::Type type);
std::ostream& operator<< (std::ostream& os, GetRequest::Type type);
