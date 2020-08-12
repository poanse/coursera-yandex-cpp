#include "airline_ticket.h"
#include "test_runner.h"
#include <string>
#include <iostream>
using namespace std;

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time
#define UPDATE_FIELD(ticket, field, values)			\
  {																							\
		auto it = values.find( #field );						\
		if (it != values.end()) {								 		\
			istringstream is(it->second); 						\
			is >> ticket.field ;										 	\
		}																						\
	}

#define EQUAL(year) lhs.year == rhs.year

istream& operator>> (istream& is, Date& date) {
	char ch1, ch2;
	is >> date.year >> ch1 >> date.month >> ch2 >> date.day;
	if (is && ch1 == '-' && ch2 == '-') {
		return is;
	}
	throw invalid_argument("");
}
istream& operator>> (istream& is, Time& time) {
	char ch;
	is >> time.hours >> ch >> time.minutes;
	if (is && ch == ':') {
		return is;
	}
	throw invalid_argument("");
}

ostream& operator<< (ostream& os, const Date& date) {
	os << date.year << '-' << date.month << '-' << date.day;
	return os;
}
ostream& operator<< (ostream& os, const Time& time) {
	os << time.hours << ':' << time.minutes;
	return os;
}


bool operator== (const Date& lhs, const Date& rhs) {
	return EQUAL(year) && EQUAL(month) && EQUAL(day);
}
bool operator== (const Time& lhs, const Time& rhs) {
	return EQUAL(hours) && EQUAL(minutes);
}
bool operator< (const Date& lhs, const Date& rhs) {
	if (lhs.year != rhs.year) {
		return lhs.year < rhs.year;
	}
	if (lhs.month != rhs.month) {
		return lhs.month < rhs.month;
	}
	return lhs.day < rhs.day;
}

bool operator< (const Time& lhs, const Time& rhs) {
	if (lhs.hours != rhs.hours) {
		return lhs.hours < rhs.hours;
	}
	return lhs.minutes < rhs.minutes;
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
