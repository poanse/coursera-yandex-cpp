#include "route.h"

#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

constexpr long double PI = 3.1415926535;
const int EARTH_RADIUS = 6371;
// Implementation

list<string> SplitBySubstring (string str, string substr) {
	list<string> strings;
	for (size_t pos = str.find(substr); 
			pos != string::npos; 
			pos = str.find(substr)) {
		strings.push_back(str.substr(0, pos));
		str = str.substr(pos + substr.size());
	}
	strings.push_back(str.substr(0));
	return strings;
}


Stop::Stop(string n, long double lat, long double lon)
	: name(n)
	, latitude(lat)
	, longitude(lon)
{
}

long double Stop::toRadians(const long double degree) { 
	constexpr long double one_deg = PI / 180; 
	return (one_deg * degree); 
} 
  
long double Stop::ComputeDistance(const Stop* lhs, const Stop* rhs) {
	// Convert the latitudes  
	// and longitudes 
	// from degree to radians. 
	auto lat1 = Stop::toRadians(lhs->latitude); 
	auto long1 = Stop::toRadians(lhs->longitude); 
	auto lat2 = Stop::toRadians(rhs->latitude); 
	auto long2 = Stop::toRadians(rhs->longitude); 
		
	// Haversine Formula 
	long double dlong = long2 - long1; 
	long double dlat = lat2 - lat1; 

	long double ans = pow(sin(dlat / 2), 2) + 
		cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2); 

	ans = 2 * asin(sqrt(ans)); 

	// Radius of Earth in  
	// Kilometers, R = 6371 
	// Use R = 3956 for miles 
	long double R = 6371; 
		
	// Calculate the result 
	ans = ans * R; 
	return ans; 
}

Route::Info::Info(string b, bool is, list<string> stps)
	: bus(b)
	, is_circular(is)
	, stops(stps)
{
	if (stops.empty()) {
		throw invalid_argument("RouteInfo: list if stops is empty");
	}
}

Route::InfoPtr Route::Parser(string bus, string unparsed_stops) {
	list<string> stops;
	bool is_circular;
	if (unparsed_stops.find('-') != string::npos) {
		is_circular = false;
		stops = SplitBySubstring(move(unparsed_stops), " - ");
	} else if (unparsed_stops.find('>') != string::npos) {
		is_circular = true;
		stops = SplitBySubstring(move(unparsed_stops), " > ");
		stops.pop_back();
	} else {
		throw std::invalid_argument("Can't parse string: \"" + unparsed_stops + "\"");
	}
	return make_unique<Route::Info>(bus, is_circular, move(stops));
}

Route::Stats::Stats(const Info* info, const Stops* stops) {
	unordered_set<string> unique_stops {
		info->stops.begin(), info->stops.end()
	};
	n_unique_stops = unique_stops.size();
	for (auto it = info->stops.begin(); it != prev(info->stops.end()); it++) {
		route_length += Stop::ComputeDistance(
				stops->at(*it).get(), stops->at(*next(it)).get()
		);
	}
	if (info->is_circular) {
		n_stops = info->stops.size() + 1;
		route_length += Stop::ComputeDistance(
				stops->at(info->stops.back()).get(), 
				stops->at(info->stops.front()).get()
		);
	} else {
		n_stops = info->stops.size() * 2 - 1;
		route_length *= 2;
	}
}

Route::Route(InfoPtr route_info)
	:	info(move(route_info))
{
}

void Route::CalculateStats(const Stops* stops) {
	stats = make_shared<Route::Stats>(info.get(), stops);
}
