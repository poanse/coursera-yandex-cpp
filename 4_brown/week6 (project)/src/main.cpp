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
//#include "route_manager.h"
//#include "route.h"
#include "requests.h"

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


int main() {
	RunTests();
	Run(cin, cout);
	// TBD : output
	// TBD : split into several files
}
