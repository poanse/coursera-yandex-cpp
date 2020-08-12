#include "stats.h"
#include <stdexcept>

const set<string_view> Stats::valid_methods {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
const set<string_view> Stats::valid_uris {"/", "/order", "/product", "/basket", "/help", "unknown"};

Stats::Stats() 
	: method_stats()
	, uri_stats()
{
	for (auto& x: valid_methods) {
		method_stats[x] = 0;
	}
	for (auto& x: valid_uris) {
		uri_stats[x] = 0;
	}
}

bool Stats::IsValidMethod(string_view method) const {
	return valid_methods.count(method);
}
bool Stats::IsValidUri(string_view uri) const {
	return valid_uris.count(uri);
}
void Stats::AddMethod(string_view method) {
	if (IsValidMethod(method)) {
		method_stats[method]++;
	} else {
		method_stats["UNKNOWN"]++;
	}
}

void Stats::AddUri(string_view uri) {
	if (IsValidUri(uri)) {
		uri_stats[uri]++;
	} else {
		uri_stats["unknown"]++;
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return method_stats;
}
const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats;
}


HttpRequest ParseRequest(string_view line) {
	HttpRequest req;
	auto start = 0;
	while (line[start] == ' ') {
		start++;
	}
	auto pos = line.find(' ', start);
	if (pos == string::npos) {
		throw invalid_argument("Invalid request: " + string(line));
	}
	auto pos2 = line.find(' ', pos + 1);
	if (pos2 == string::npos) {
		throw invalid_argument("Invalid request: " + string(line));
	}
	req.method = line.substr(start, pos - start);
	req.uri = line.substr(pos + 1, pos2 - pos - 1);
	req.protocol = line.substr(pos2 + 1);
	return req;
}
