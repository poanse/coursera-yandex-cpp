#include "route.h"

#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <stdexcept>
#include <cmath>
#include <iostream>

#include "requests.h"

using namespace std;

constexpr double PI = 3.1415926535;
const int EARTH_RADIUS = 6371;
// Implementation

vector<string> SplitBySubstring (string str, string substr) {
	vector<string> strings;
	for (size_t pos = str.find(substr); 
			pos != string::npos; 
			pos = str.find(substr)) {
		strings.push_back(str.substr(0, pos));
		str = str.substr(pos + substr.size());
	}
	strings.push_back(str.substr(0));
	return strings;
}


Stop::Stop(string n, double lat, double lon)
	: name(n)
	, latitude(lat)
	, longitude(lon)
{
}

double Stop::toRadians(const double degree) { 
	constexpr double one_deg = PI / 180; 
	return (one_deg * degree); 
} 
  
double Stop::ComputeDistance(const Stop* lhs, const Stop* rhs) {
	// Convert the latitudes  
	// and longitudes 
	// from degree to radians. 
	auto lat1 = Stop::toRadians(lhs->latitude); 
	auto long1 = Stop::toRadians(lhs->longitude); 
	auto lat2 = Stop::toRadians(rhs->latitude); 
	auto long2 = Stop::toRadians(rhs->longitude); 
		
	// Haversine Formula 
	double dlong = long2 - long1; 
	double dlat = lat2 - lat1; 

	double ans = pow(sin(dlat / 2), 2) + 
		cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2); 

	ans = 2 * asin(sqrt(ans)); 

	// Radius of Earth in  
	// Kilometers, R = 6371 
	// Use R = 3956 for miles 
	double R = 6371; 
		
	// Calculate the result 
	ans = ans * R; 
	return ans*1000; 
}

Route::Info::Info(string b, bool is, vector<string> stops_)
	: bus(b)
	, is_circular(is)
	, stops(stops_)
{
	if (stops.empty()) {
		throw invalid_argument("RouteInfo: list if stops is empty");
	}
}

Route::InfoPtr Route::Parser(string bus, string unparsed_stops) {
	vector<string> stops;
	bool is_circular;
	if (unparsed_stops.find('-') != string::npos) {
		is_circular = false;
		stops = SplitBySubstring(move(unparsed_stops), " - ");
	} else if (unparsed_stops.find('>') != string::npos) {
		is_circular = true;
		stops = SplitBySubstring(move(unparsed_stops), " > ");
		// stops.pop_back();
	} else {
		throw std::invalid_argument("Can't parse string: \"" + unparsed_stops + "\"");
	}
	return make_unique<Route::Info>(bus, is_circular, move(stops));
}

double GetRouteLength(const Route::Info* info, const Stops* stops) {
	if (info->stops.empty()) {
		return 0;
	}
	double route_length = 0;
	for (auto it = next(info->stops.begin()); it != info->stops.end(); it++) {
		route_length += Stop::ComputeDistance( 
			stops->at(*prev(it)).get(), 
			stops->at(*it).get() 
		);
	}
	if (!info->is_circular) {
		route_length *= 2;
	}
	return route_length;
}

inline int GetStopsDistanceTrue(const string& stop1, const string& stop2, 
		const Distances& distances) {
	return distances.GetDistance(stop1, stop2);
}

double GetRouteLengthTrue(const Route::Info* info,	
		const Distances& distances) {
	if (info->stops.empty()) {
		return 0;
	}
	double route_length_true = 0;
	for (auto it = next(info->stops.begin()); it != info->stops.end(); it++) {
		route_length_true += GetStopsDistanceTrue(*prev(it), *it, distances);
		if (!info->is_circular) {
			route_length_true += GetStopsDistanceTrue(*it, *prev(it), distances);
		}
	}
	return route_length_true;
}

Route::Stats::Stats(const Info* info, const Stops* stops, const Distances& distances) 
	: route_length(GetRouteLength(info, stops))
	, route_length_true(GetRouteLengthTrue(info, distances))
	, curvature(route_length_true / route_length)
	, n_stops(info->is_circular ? info->stops.size() : info->stops.size()*2 - 1)
{
	set<string> unique_stops { info->stops.begin(), info->stops.end() };
	n_unique_stops = unique_stops.size();
}

void Route::CalculateStats(const Stops* stops, const Distances& distances) {
	stats = make_shared<Route::Stats>(info.get(), stops, distances);
}