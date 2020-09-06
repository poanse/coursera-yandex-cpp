#include "run.h"

#include <iostream>
#include <iomanip>

#include "route_manager.h"
#include "responses.h"
#include "requests.h"
#include "parse_json.h"
#include "json.h"

using namespace std;

void Run(istream& is, ostream& os) {
	os << setprecision(20);
	RouteManager rm;
	size_t N, M;
	is >> N;
	ResponsePtr ptr;
	for (size_t i = 0; i < N; i++) {
		auto req_ptr = ReadAddRequest(is);
		rm.ProcessAddRequest(move(req_ptr));
	}
	is >> M;
	for (size_t i = 0; i < M; i++) {
		auto req_ptr = ReadGetRequest(is);
		auto ptr = rm.ProcessGetRequest(move(req_ptr));
		ptr->Process(os);
	}
}

void RunJson(istream& is, ostream& os) {
	os << setprecision(20);
	RouteManager rm;
	auto root = Json::Load(is).GetRoot().AsMap();
	auto add_requests = root["base_requests"].AsArray();
	for (const auto& add_req_node : add_requests) {
		auto req_ptr = GetAddRequestFromJson(add_req_node);
		rm.ProcessAddRequest(move(req_ptr));
	}
	auto get_requests = root["stat_requests"].AsArray();
	vector<ResponsePtr> responses;
	responses.reserve(get_requests.size());
	for (const auto& get_req_node : get_requests) {
		auto req_ptr = GetGetRequestFromJson(get_req_node);
		responses.push_back(rm.ProcessGetRequest(move(req_ptr)));
	}
	ProcessResponsesJson(os, responses);
}
