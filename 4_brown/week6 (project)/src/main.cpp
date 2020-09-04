#include <iostream>
#include <string>
#include <string_view>
#include <list>
#include <memory>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>

#include "test_runner.h"
#include "tests.h"
#include "json.h"
#include "parse_json.h"
//#include "route_manager.h"
//#include "route.h"
#include "requests.h"
#include "responses.h"

using namespace std;

void Run(istream& is, ostream& os) {
	os << setprecision(20);
	RouteManager rm;
	size_t N, M;
	is >> N;
	ResponsePtr ptr;
	for (size_t i = 0; i < N; i++) {
		ptr = rm.ProcessAddRequest(ReadAddRequest(is));
	}
	is >> M;
	for (size_t i = 0; i < M; i++) {
		ptr = rm.ProcessGetRequest(ReadGetRequest(is));
		ProcessResponse(os, ptr.get());
	}
}

void RunJson(istream& is, ostream& os) {
	os << setprecision(20);
	RouteManager rm;
	auto root = Json::Load(is).GetRoot().AsMap();
	auto add_requests = root["base_requests"].AsArray();
	auto get_requests = root["stat_requests"].AsArray();
	for (const auto& add_req_node : add_requests) {
		auto add_request = GetAddRequestFromJson(add_req_node);
		rm.ProcessAddRequest(move(add_request));
	}
	vector<ResponsePtr> responses;
	responses.reserve(get_requests.size());
	for (const auto& get_req_node : get_requests) {
		auto get_request = GetGetRequestFromJson(get_req_node);
		responses.push_back(rm.ProcessGetRequest(move(get_request)));
	}
	ProcessResponsesJson(os, responses);
}


int main() {
	RunTests();
	//Run(cin, cout);
	RunJson(cin, cout);
}
