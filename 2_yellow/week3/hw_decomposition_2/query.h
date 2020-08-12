#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
	std::string bus;
  std::string stop;
  std::vector<std::string> stops;
};

const std::map<std::string, QueryType> StrToOpCode{
	{"NEW_BUS", QueryType::NewBus},
	{"BUSES_FOR_STOP", QueryType::BusesForStop},
	{"STOPS_FOR_BUS", QueryType::StopsForBus},
	{"ALL_BUSES", QueryType::AllBuses},
};

 std::istream& operator >> (std::istream& is, Query& q);
