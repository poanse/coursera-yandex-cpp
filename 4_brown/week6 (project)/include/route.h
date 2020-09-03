#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <list>
#include <stdexcept>

//#include "requests.h"

class RouteManager;

std::list<std::string> SplitBySubstring (std::string str, std::string substr);

struct Stop {
	std::string name;
	double latitude;
	double longitude;

	Stop(std::string n, double lat, double lon);
	
	static double toRadians(const double degree);

	static double ComputeDistance(const Stop* lhs, const Stop* rhs);
};
using StopPtr = std::unique_ptr<Stop>;
using Stops = std::unordered_map<std::string, StopPtr>;


struct Route {
	struct Info {
		std::string bus;
		bool is_circular;
		std::list<std::string> stops;

		Info(std::string b, bool is, std::list<std::string> stps);
	};

	using InfoPtr = std::unique_ptr<Info>;

	static InfoPtr Parser(std::string bus, std::string unparsed_stops);

	struct Stats {
		size_t n_stops = 0;
		size_t n_unique_stops = 0;
		double route_length = 0;
		double route_length_true = 0;
		double curvature = 1;

		Stats(const Info* info, const Stops* stops, const RouteManager* rm);
	};
	using StatsPtr = std::shared_ptr<Stats>;

	const InfoPtr info;
	StatsPtr stats = nullptr;

	Route(InfoPtr route_info);

	void CalculateStats(const Stops* stops, const RouteManager* rm);
};
using RoutePtr = std::unique_ptr<Route>;
