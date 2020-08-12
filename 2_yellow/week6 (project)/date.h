#pragma once
#include <iostream>
#include <string>

class Date {
public:
	//Date() = default;
	Date(int y, int m, int d) {
		year = y;
		if (m < 0 || m > 9999) {
			throw std::invalid_argument("Year value is invalid: " + std::to_string(y));
		}
		if (m < 1 || m > 12) {
			throw std::invalid_argument("Month value is invalid: " + std::to_string(m));
		}
		if (d < 1 || d > 31) {
			throw std::invalid_argument("Day value is invalid: " + std::to_string(d));
		}
		month = m;
		day = d;
	}

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

std::ostream& operator<< (std::ostream& os, const Date& date);

Date ParseDate (std::istream& is);
