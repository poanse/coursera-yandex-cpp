#pragma once
#include <string>
#include <iostream>

struct StopPair {
	std::pair<std::string, std::string> stops;
	StopPair(std::string a, std::string b);
};

bool operator==(const StopPair& lhs, const StopPair& rhs);

std::ostream& operator<<(std::ostream& os, const StopPair& p);

namespace std {
	template<>
	struct hash<StopPair> {
		size_t operator()(const StopPair& x) const {
			size_t v1 = hash<string>()(x.stops.first);
			size_t v2 = hash<string>()(x.stops.second);
			return v1 * 3517 + v2;
		}
	};
};

