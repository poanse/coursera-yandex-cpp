#pragma once
#include <string>

using StopPair = std::pair<std::string, std::string>;

namespace std {
	template<>
	struct hash<StopPair> {
		size_t operator()(const StopPair& p) const {
			size_t v1 = hash<string>()(p.first);
			size_t v2 = hash<string>()(p.second);
			return v1 * 3517 + v2;
		}
	};
};