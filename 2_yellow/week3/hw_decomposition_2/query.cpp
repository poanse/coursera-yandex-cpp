#include "query.h"

using namespace std;

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
	q = Query();
	string operation_code;
	int stop_count;
	is >> operation_code;
	if (StrToOpCode.count(operation_code) == 0) {
		return is;
	} 
	q.type = StrToOpCode.at(operation_code);
	switch (q.type) {
		case QueryType::NewBus:
			is >> q.bus;
			is >> stop_count;
			q.stops.resize(stop_count);
			for (auto& stop : q.stops) {
				is >> stop;
			}
			break;
		case QueryType::BusesForStop:
			is >> q.stop;
			break;
		case QueryType::StopsForBus:
			is >> q.bus;
			break;
		case QueryType::AllBuses:
			break;
	}
  return is;
}
