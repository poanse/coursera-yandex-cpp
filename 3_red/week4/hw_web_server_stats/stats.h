#pragma once

#include "http_request.h"

#include <string>
#include <string_view>
#include <map>
#include <unordered_set>
#include <set>
using namespace std;

class Stats {
public:
	Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
	map<string_view, int> method_stats;
	map<string_view, int> uri_stats;

	static const set<string_view> valid_methods;
	static const set<string_view> valid_uris;

	bool IsValidMethod(string_view method) const;
	bool IsValidUri(string_view uri) const;
};

HttpRequest ParseRequest(string_view line);

