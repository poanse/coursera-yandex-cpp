#include "database.h"
#include <algorithm>
using namespace std;

void Database::Add(const Date& date, const Event& event) {
	auto& events_set = date_to_events_set[date];
	if (0 == events_set.count(event)) {
		date_to_events[date].push_back(event);
		events_set.insert(event);
	}
}

void Database::Print(std::ostream& os) const {
	for (const auto& [date, events] : date_to_events) {
		for (const auto& event : events) {
			os << date << ' ' << event << '\n';
		}
	}
}

Entry Database::Last(const Date& date) const {
	auto it = date_to_events.upper_bound(date);
	if (it == date_to_events.begin()) {
		throw invalid_argument("");
	}
	it--;
	while (it->second.empty() && it != date_to_events.begin()) {
		it--;
	}
	if (it->second.empty() && it == date_to_events.begin()) {
		throw invalid_argument("");
	}
	return {it->first, it->second.back()};
}
