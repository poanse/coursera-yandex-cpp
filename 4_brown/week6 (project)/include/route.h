#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "stop_pair.h"
#include "distances.h"

std::vector<std::string> SplitBySubstring (std::string_view str, std::string_view substr);

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
		std::vector<std::string> stops;

		Info(std::string b, bool is, std::vector<std::string> stops);
	};
	struct Stats {
		double route_length = 0;
		int route_length_true = 0;
		double curvature = 1;
		size_t n_stops = 0;
		size_t n_unique_stops = 0;

		Stats(const Info*, const Stops*, const Distances&);
	};
	using InfoPtr = std::unique_ptr<Info>;
	using StatsPtr = std::shared_ptr<Stats>;

	const InfoPtr info;
	StatsPtr stats = nullptr;

	Route(InfoPtr route_info)	:	info(move(route_info)) {}
	static InfoPtr Parser(const std::string& bus, const std::string& unparsed_stops);
	void CalculateStats(const Stops*, const Distances&);
};
using RoutePtr = std::unique_ptr<Route>;
