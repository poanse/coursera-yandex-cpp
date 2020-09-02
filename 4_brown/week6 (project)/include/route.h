#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <list>
#include <stdexcept>

std::list<std::string> SplitBySubstring (std::string str, std::string substr);

struct Stop {
	std::string name;
	long double latitude;
	long double longitude;

	Stop(std::string n, long double lat, long double lon);
	
	static long double toRadians(const long double degree);

	static long double ComputeDistance(const Stop* lhs, const Stop* rhs);
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
		long double route_length = 0;

		Stats(const Info* info, const Stops* stops);
	};
	using StatsPtr = std::shared_ptr<Stats>;

	const InfoPtr info;
	StatsPtr stats = nullptr;

	Route(InfoPtr route_info);

	void CalculateStats(const Stops* stops);
};
using RoutePtr = std::unique_ptr<Route>;
