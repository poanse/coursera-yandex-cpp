#include <iostream>
#include <string>
#include <string_view>
#include <list>
#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "test_runner.h"
#include "tests.h"
#include "route_manager.h"
#include "route.h"

using namespace std;

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSplitBySubstring);
	RUN_TEST(tr, TestReadAddRequest);
	RUN_TEST(tr, TestReadGetRequest);
	// TBD : cover code with unit tests:

	RouteManager rm;
	size_t N, M;
	cin >> N;
	ResponsePtr ptr;
	for (size_t i = 0; i < N; i++) {
		ptr = rm.ProcessAddRequest(ReadAddRequest(cin));
	}
	cin >> M;
	for (size_t i = 0; i < M; i++) {
		ptr = rm.ProcessGetRequest(ReadGetRequest(cin));
		ProcessResponse(cout, ptr.get());
	}
	// TBD : output
	// TBD : split into several files
}
