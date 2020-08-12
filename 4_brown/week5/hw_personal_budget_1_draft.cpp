#include <iostream>
#include <ctime>

using namespace std;

const int SECONDS_IN_DAY = 60 * 60 * 24;

struct Date {
	size_t year_;
	size_t month_;
	size_t day_;

	time_t AsTimestamp() const {
		std::tm t;
		t.tm_sec   = 0;
		t.tm_min   = 0;
		t.tm_hour  = 0;
		t.tm_mday  = day_;
		t.tm_mon   = month_ - 1;
		t.tm_year  = year_ - 2000;
		t.tm_isdst = 0;
		return mktime(&t);
	}

	size_t AsDays() const {
		return AsTimestamp() / SECONDS_INT_DAY;
	}
};

//int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  //const time_t timestamp_to = date_to.AsTimestamp();
  //const time_t timestamp_from = date_from.AsTimestamp();
  //return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
//}

struct Range {
	// [start, end)
	size_t start;
	size_t end;
	double value; // per day
}

bool operator< (const Range& lhs, const Range& rhs) {
	return lhs.start < rhs.start;
}
bool operator< (const Range& lhs, size_t rhs) {
	return lhs.start < rhs;
}

class BudgetManager {
private:
	set<Range> ranges;
public:
	void Earn(const Date& start_date, const Date& end_date, size_t value) {
		auto start = start_date.AsDays();
		auto end = end_date.AsDays() + 1;
	}

	PayTax();

	double ComputeIncome(const Date& start_date, const Date& end_date) const {
		auto start = start_date.AsDays();
		auto end = end_date.AsDays() + 1;
		double income = 0;
		auto it = prev(ranges.upper_bound(start));
		while (it != ranges.end()) {
			auto& range = *it;
			if (range.start >= start) {
				if (range.end < end) {
					income += range.value * (range.end - range.start);
				} else {
					income += range.value * (end - range.start);
					break;
				}
			}
		}
		return income;
	}
};

int main() {


}

