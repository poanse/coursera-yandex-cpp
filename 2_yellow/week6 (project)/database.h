#pragma once
#include "date.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include <algorithm>

using Event = std::string;
using Entry = std::pair<Date, std::string_view>;

template <typename T, typename U>
std::ostream& operator<< (std::ostream& os, const std::pair<T,U>& p) {
	os << p.first << ' ' << p.second;
	return os;
}


class Database {
public:
	void Add(const Date& date, const Event& event);

	void Print(std::ostream& os) const;

	template <typename Predicate>
	int RemoveIf(Predicate pred);

	template <typename Predicate>
	std::vector<Entry> FindIf(Predicate pred) const;

	Entry Last(const Date& date) const;
private:
	std::map<Date, std::vector<Event>> date_to_events;
	std::map<Date, std::set<Event>> date_to_events_set;
};

template <typename Predicate>
int Database::RemoveIf(Predicate pred) {
	int count = 0;
	if (date_to_events.begin() == date_to_events.end()) {
		return count;
	}

	auto lambda = [&](std::map<Date, std::vector<Event>>::iterator& it){
		auto date = it->first;
		auto& events = it->second;
		auto events_it = stable_partition(events.begin(), events.end(), 
				[&](const Event& event){ return !pred(date, event); }
		);
		if (events_it == events.begin()) {
			count += events.size();
			date_to_events_set.erase(date);
			date_to_events.erase(it);
		} else if (events_it != events.end()) {
			count += distance(events_it, events.end());
			auto& events_set = date_to_events_set[date];
			for (auto it_ = events_it; it_ != events.end();it_++) {
				events_set.erase(*it_);
			}
			events.erase(events_it, events.end());
		}
	};

	for (auto next_it = next(date_to_events.begin()); 
			next_it != date_to_events.end(); next_it++){
		auto it = prev(next_it);
		lambda(it);
	}
	auto it = prev(date_to_events.end());
	lambda(it);
	//for (auto it = date_to_events.begin(); it != date_to_events.end();it++){
		//auto& date = it->first;
		//auto& events = it->second;
		//auto events_it = remove_if(events.begin(), events.end(), 
				//[pred, &date](const Event& event){return pred(date, event);}
		//);
		//count += distance(events_it, events.end());
		//events.erase(events_it, events.end());
		//if (it != date_to_events.begin() && prev(it)->second.empty()) {
			//date_to_events.erase(prev(it));
		//}
	//}
	//if (date_to_events.end() != date_to_events.begin() 
			//&& prev(date_to_events.end())->second.empty()) {
		//date_to_events.erase(prev(date_to_events.end()));
	//}
	return count;
}

template <typename Predicate>
std::vector<Entry> Database::FindIf(Predicate pred) const {
	std::vector<Entry> output;
	for (const auto& [date, events] : date_to_events) {
		for (const auto& event : events) {
			if (pred(date, event)) {
				output.emplace_back(date, event);
			}
		}
	}
	return output;
}

