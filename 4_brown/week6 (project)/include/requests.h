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

using AddRequestPtr = std::unique_ptr<AddRequest>;
using AddRouteRequestPtr = std::unique_ptr<AddRouteRequest>;
using AddStopRequestPtr = std::unique_ptr<AddStopRequest>;

using GetRequestPtr = std::unique_ptr<GetRequest>;
using GetBusRequestPtr = std::unique_ptr<GetBusRequest>;
using GetStopRequestPtr = std::unique_ptr<GetStopRequest>;

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

	AddRouteRequest(AddRequest::Type type_, Route::InfoPtr ptr)
		:	AddRequest(type_)
		, route(std::move(ptr))
	{
	}
};

struct AddStopRequest : AddRequest {
	StopPtr stop;
	std::unordered_map<StopPair, int> distances;
	AddStopRequest(AddRequest::Type, StopPtr, Distances);
};

using Id = int;
using Buses = std::set<std::string>;

struct GetRequest {
	enum class Type {
		GET_BUS_INFO,
		GET_STOP_INFO
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

	GetBusRequest(GetRequest::Type type_, std::string b, Id id_ = 0)
		: GetRequest(type_, id_)
		, bus(b)
	{
	}
};

struct GetStopRequest : GetRequest {
	std::string stop;

	GetStopRequest(GetRequest::Type type_, std::string s, Id id_ = 0)
		: GetRequest(type_, id_)
		, stop(s)
	{
	}
};

AddRequestPtr ReadAddRequest(std::istream& is);
GetRequestPtr ReadGetRequest(std::istream& is);

std::ostream& operator<< (std::ostream&, AddRequest::Type);
std::ostream& operator<< (std::ostream&, GetRequest::Type);
