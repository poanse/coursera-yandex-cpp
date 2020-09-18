#include "responses.h"
#include "json.h"

#include <iomanip>
#include <iostream>
#include <map>

void ProcessResponsesJson(std::ostream& os, const std::vector<ResponsePtr>& responses) {
	std::vector<Json::Node> nodes;
	for (const auto& response : responses) {
		nodes.push_back(response->GetJson());
	}
	os << std::setprecision(14);
	Json::PrintValue(nodes, os);
}
   
GetBusResponse::GetBusResponse(Route::StatsPtr stats_, std::string bus_, int id_ = 0) 
	: Response(id_)
	, stats(std::move(stats_))
	, bus(std::move(bus_))
{
}

GetStopResponse::GetStopResponse(std::string stop_, bool found_, 
			std::set<std::string> buses_ = {}, int id_ = 0)
	: Response(id_)
	, stop(std::move(stop_))
	, found(found_)
{
	if (found) {
		buses = std::move(buses_);
	}
}

Json::Node GetBusResponse::GetJson() const {
	Json::Dict dict;
	dict["request_id"] = id;
	if (!stats) {
		dict["error_message"] = "not found";
	} else {
		dict["route_length"] = stats->route_length_true;
		dict["curvature"] = stats->curvature;
		dict["stop_count"] = int(stats->n_stops);
		dict["unique_stop_count"] = int(stats->n_unique_stops);
	}
	return dict;
}

Json::Node GetStopResponse::GetJson() const {
	Json::Dict dict;
	dict["request_id"] = id;
	if (found) {
		dict["buses"] = std::vector<Json::Node>(begin(buses), end(buses));
	} else {
		dict["error_message"] = "not found";
	}
	return dict;
}

Json::Node GetRouteResponse::GetJson() const {
	std::vector<Json::Node> items;
	Json::Dict item;
	double total_weight = 0;
	if (steps) {
		for (auto& step : steps.value()) {
			total_weight += step.weight;

			item["type"] = "Wait";
			item["time"] = bus_wait_time;
			item["stop_name"] = step.stop_from;
			items.push_back(move(item));

			item["type"] = "Bus";
			item["span_count"] = step.stop_count;
			item["time"] = step.weight - bus_wait_time;
			item["bus"] = step.bus;
			items.push_back(move(item));
		}
	}

	Json::Dict dict;
	dict["request_id"] = id;
	if (steps) {
		dict["total_time"] = total_weight;
		dict["items"] = move(items);
	} else {
		dict["error_message"] = "not found";
	}
	return dict;
}