#pragma once
#include <iostream>
#include <optional>
#include <memory>
#include "route.h"

struct AddRequest {
	enum class Type {
		ADD_ROUTE, 
		ADD_STOP,
	};

	AddRequest::Type type;
	std::optional<Route::InfoPtr> route;
	std::optional<StopPtr> stop;

	AddRequest(AddRequest::Type type_, Route::InfoPtr ptr);
	AddRequest(AddRequest::Type type_, StopPtr ptr);
};

struct GetRequest {
	enum class Type {
		GET_BUS_INFO
	};
	GetRequest::Type type;
	std::optional<std::string> bus;

	GetRequest(GetRequest::Type type_, std::string b);
};

using AddRequestPtr = std::unique_ptr<AddRequest>;
using GetRequestPtr = std::unique_ptr<GetRequest>;


struct Response {
	std::optional<Route::StatsPtr> stats;
	//std::optional<string_view> message;
	Response(Route::StatsPtr stats_);
	Response(Route::StatsPtr stats_, GetRequestPtr getreq_);
	//Response(string msg);
	// TBD
	//std::optional<AddRequestPtr> addreq;
	std::optional<GetRequestPtr> getreq;
};

using ResponsePtr = std::unique_ptr<Response>;

void ProcessResponse(std::ostream& os, const Response* resp);

AddRequestPtr ReadAddRequest(std::istream& is);

GetRequestPtr ReadGetRequest(std::istream& is);

std::ostream& operator<< (std::ostream& os, AddRequest::Type type);
std::ostream& operator<< (std::ostream& os, GetRequest::Type type);
