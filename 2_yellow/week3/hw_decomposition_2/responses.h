#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

struct BusesForStopResponse {
  // Наполните полями эту структуру
	const std::vector<std::string>* buses;
};

 std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  // Наполните полями эту структуру
	std::string bus;
	const std::vector<std::pair<std::string, const std::vector<std::string>*>> stops_n_buses;
};
 std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  // Наполните полями эту структуру
	const std::map<std::string, std::vector<std::string>>* buses_to_stops;
};

 std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
