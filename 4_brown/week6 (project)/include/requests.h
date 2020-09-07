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
class GetRouteRequest;

using AddRequestPtr = std::unique_ptr<AddRequest>;
using AddRouteRequestPtr = std::unique_ptr<AddRouteRequest>;
using AddStopRequestPtr = std::unique_ptr<AddStopRequest>;

using GetRequestPtr = std::unique_ptr<GetRequest>;
using GetBusRequestPtr = std::unique_ptr<GetBusRequest>;
using GetStopRequestPtr = std::unique_ptr<GetStopRequest>;
using GetRouteRequestPtr = std::unique_ptr<GetRouteRequest>;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s);

struct AddRequest {
	enum class Type {
		ADD_ROUTE, 
		ADD_STOP,
	};
	AddRequest::Type type;
	AddRequest(AddRequest::Type type_) : type(type_) {}
	virtual ~AddRequest() = default;
};

AddRequest::Type GetAddRequestCode(const std::string& type);

struct AddRouteRequest : AddRequest {
	Route::InfoPtr route;
	AddRouteRequest(Route::InfoPtr ptr)
		:	AddRequest(AddRequest::Type::ADD_ROUTE)
		, route(std::move(ptr))
	{
	}
};

struct AddStopRequest : AddRequest {
	StopPtr stop;
	std::unordered_map<StopPair, int> distances;
	AddStopRequest(StopPtr, std::unordered_map<StopPair, int>);
};

using Id = int;
using Buses = std::set<std::string>;

struct GetRequest {
	enum class Type {
		GET_BUS_INFO,
		GET_STOP_INFO,
		GET_ROUTE_INFO
	};

	GetRequest::Type type;
	Id id;

	GetRequest(GetRequest::Type type_, Id id_) 
		: type(type_)
	  , id(id_)
	{
	}
	virtual ~GetRequest() = default;
};

GetRequest::Type GetGetRequestCode(const std::string& type);

struct GetBusRequest : GetRequest {
	std::string bus;

	GetBusRequest(Id id_, std::string b)
		: GetRequest(GetRequest::Type::GET_BUS_INFO, id_)
		, bus(b)
	{
	}
};

struct GetStopRequest : GetRequest {
	std::string stop;

	GetStopRequest(Id id_, std::string s)
		: GetRequest(GetRequest::Type::GET_STOP_INFO, id_)
		, stop(s)
	{
	}
};

struct GetRouteRequest : GetRequest {
	std::string from;
	std::string to;
	GetRouteRequest(Id id_,
									std::string from_, 
									std::string to_)
		: GetRequest(GetRequest::Type::GET_ROUTE_INFO, id_)
		, from(std::move(from_))
		, to(std::move(to_))
	{
	}
};

// AddRequestPtr ReadAddRequest(std::istream& is);
// GetRequestPtr ReadGetRequest(std::istream& is);

std::ostream& operator<< (std::ostream&, AddRequest::Type);
std::ostream& operator<< (std::ostream&, GetRequest::Type);
