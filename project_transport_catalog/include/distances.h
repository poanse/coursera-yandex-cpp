#pragma once
#include <string>
#include <unordered_map>
#include "stop_pair.h"

class Distances : public std::unordered_map<StopPair, int> {
public:
	int GetDistance(const std::string& stop1, const std::string& stop2) const {
		auto it1 = find(StopPair(stop1, stop2));
		if (it1 != end()) {
			return it1->second;
		}
		return at(StopPair(stop2, stop1));
	}
};

struct RoutingSettings {
	int bus_wait_time; // minutes
	double bus_velocity; // km per hour
};
