#include "date.h"
#include <iomanip>

using namespace std;

int Date::GetYear() const {return year;}
int Date::GetMonth() const {return month;}
int Date::GetDay() const {return day;}


bool operator< (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) {
		return lhs.GetYear() < rhs.GetYear();
	}
	if (lhs.GetMonth() != rhs.GetMonth()) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetDay() < rhs.GetDay();
}

bool operator>= (const Date& lhs, const Date& rhs) {
	return !(lhs < rhs);
}

bool operator== (const Date& lhs, const Date& rhs) {
 return lhs.GetYear() == rhs.GetYear() && 
	 			lhs.GetMonth() == rhs.GetMonth() &&
	 			lhs.GetDay() == rhs.GetDay();
}
bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) {
		return lhs.GetYear() > rhs.GetYear();
	}
	if (lhs.GetMonth() != rhs.GetMonth()) {
		return lhs.GetMonth() > rhs.GetMonth();
	}
	return lhs.GetDay() > rhs.GetDay();
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return !(lhs > rhs);
}

std::ostream& operator<< (std::ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.GetYear() << '-' 
		<< setw(2) << setfill('0') << date.GetMonth() << '-'
		<< setw(2) << setfill('0') << date.GetDay();
	return os;
}

Date ParseDate (std::istream& is) {
	char ch1, ch2;
	int y, m, d;
	is >> y >> ch1 >> m >> ch2 >> d;
	if (!is || ch1 != '-' || ch2 != '-') {
		throw invalid_argument("Wrong date format: " + to_string(y) + ch1 
				+ to_string(m) + ch2 + to_string(d));
	}
	return Date(y, m, d);
}
