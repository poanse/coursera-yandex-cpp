#include <iostream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

const size_t SECONDS_IN_DAY = 60 * 60 * 24;
const size_t MAX_DAYS = 40000;
const double TAX_VALUE = 0.87;
const size_t DAYS_SHIFT = 10956;

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
		t.tm_year  = year_ - 1900;
		t.tm_isdst = 0;
		return mktime(&t);
	}

	size_t AsDays() const {
		return AsTimestamp() / SECONDS_IN_DAY - DAYS_SHIFT;
	}
};

istream& operator>> (istream& is, Date& date) {
	is >> date.year_;
	is.ignore(1);
	is >> date.month_;
	is.ignore(1);
	is >> date.day_;
	return is;
}

//int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  //const time_t timestamp_to = date_to.AsTimestamp();
  //const time_t timestamp_from = date_from.AsTimestamp();
  //return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
//}

//struct Range {
	//// [start, end)
	//size_t start;
	//size_t end;
	//double value; // per day
//};

//bool operator< (const Range& lhs, const Range& rhs) {
	//return lhs.start < rhs.start;
//}
//bool operator< (const Range& lhs, size_t rhs) {
	//return lhs.start < rhs;
//}

class BudgetManager {
private:
	vector<double> data;
public:
	BudgetManager()	{
		data = vector<double>(MAX_DAYS, 0);
		//cerr << "vector size: " << data.size() << endl;
	}

	void Earn(const Date& start_date, const Date& end_date, size_t value) {
		size_t start = start_date.AsDays();
		//cerr << start << endl;
		size_t end = end_date.AsDays() + 1;
		//cerr << end << endl;
		double daily_value = value * 1.0 / (end - start);
		for (size_t day = start; day < end; day++) {
			data[day] += daily_value;
		}
	}

	void PayTax(const Date& start_date, const Date& end_date) {
		size_t start = start_date.AsDays();
		size_t end = end_date.AsDays() + 1;
		for (size_t day = start; day < end; day++) {
			data[day] *= TAX_VALUE;
		}
	}

	double ComputeIncome(const Date& start_date, const Date& end_date) const {
		auto start = start_date.AsDays();
		auto end = end_date.AsDays() + 1;
		//cerr << start << endl;
		//cerr << end << endl;
		double income = 0;
		for (size_t day = start; day < end; day++) {
			income += data[day];
		}
		return income;
	}
};

int main() {
	BudgetManager bm;
	size_t Q, value;
	string command;
	Date start, end;
	cout.precision(25);
	cin >> Q;
	for (size_t i = 0; i < Q; i++) {
		cin >> command >> start >> end;
		//cerr << command << endl;
		//cerr << "Start: " << start.year_ << ' '<< start.month_ << ' ' 
			//<< start.day_ << ' ' << endl;
		//cerr << "End: " << end.year_ << ' '<< end.month_ << ' ' 
			//<< end.day_ << ' ' << endl;
		if (command == "Earn") {
			cin >> value;
			//cerr << "value: " << value << endl;
			bm.Earn(start, end, value);
		} else if (command == "PayTax") {
			bm.PayTax(start, end);
		} else if (command == "ComputeIncome") {
			cout << bm.ComputeIncome(start, end) << endl;
		}
	}
}

