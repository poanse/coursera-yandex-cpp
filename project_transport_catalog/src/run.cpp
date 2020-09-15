#include "run.h"

#include <iostream>
#include <iomanip>

#include "route_manager.h"
#include "responses.h"
#include "requests.h"
#include "parse_json.h"
#include "json.h"

using namespace std;

void RunJson(istream& is, ostream& os) {
	os << setprecision(20);
	auto root = Json::Load(is).GetRoot().AsMap();
	RoutingSettings rs = GetRoutingSettingsFromJson(root.at("routing_settings"));
	RouteManager rm(rs);
	auto add_requests = root.at("base_requests").AsArray();
	for (const auto& add_req_node : add_requests) {
		auto req_ptr = GetAddRequestFromJson(add_req_node);
		rm.ProcessAddRequest(move(req_ptr));
	}
	rm.InitRouter();
	auto get_requests = root.at("stat_requests").AsArray();
	vector<ResponsePtr> responses;
	responses.reserve(get_requests.size());
	for (const auto& get_req_node : get_requests) {
		auto req_ptr = GetGetRequestFromJson(get_req_node);
		responses.push_back(rm.ProcessGetRequest(move(req_ptr)));
	}
	ProcessResponsesJson(os, responses);
}