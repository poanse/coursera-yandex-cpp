#include "stop_pair.h"

StopPair::StopPair(std::string a, std::string b) {
	//if (a < b) {
		//stops = std::make_pair<std::string, std::string>(std::move(a), 
				//std::move(b));
	//} else {
		//stops = std::make_pair<std::string, std::string>(std::move(b), 
				//std::move(a));
	//}
	stops = std::make_pair<std::string, std::string>(
			std::move(a), 
			std::move(b)
	);
}

bool operator==(const StopPair& lhs, const StopPair& rhs) {
	return lhs.stops == rhs.stops;
}

std::ostream& operator<<(std::ostream& os, const StopPair& p) {
	os << p.stops.first << " - " << p.stops.second;
	return os;
}
