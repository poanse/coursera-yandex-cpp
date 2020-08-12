#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <optional>
#include <unordered_map>
#include <memory>

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


struct Request {
	enum class Type {
		EARN, SPEND, PAY_TAX, COMPUTE_INCOME
	};

	using Answer = optional<double>;

	Request(Request::Type rtype, Date start, Date end, 
			optional<int> value_ = nullopt) 
		: request_type(rtype)
		, start_date(start)
		, end_date(end)
		, value(value_)
	{
	}

	Request::Type request_type;
	Date start_date;
	Date end_date;
	optional<int> value;
};

const unordered_map<string_view, Request::Type> RequestTypeFromStr = 
{
	{"Earn", Request::Type::EARN},
	{"Spend", Request::Type::SPEND},
	{"PayTax", Request::Type::PAY_TAX},
	{"ComputeIncome", Request::Type::COMPUTE_INCOME},
};

unique_ptr<Request> ReadRequest(istream& is) {
	string command;
	Date start, end;
	is >> command >> start >> end;
	Request::Type rtype = RequestTypeFromStr.at(command);
	unique_ptr<Request> req;
	if (rtype != Request::Type::COMPUTE_INCOME) {
		int value;
		is >> value;
		req = make_unique<Request>(rtype, start, end, value);
	} else {
		req = make_unique<Request>(rtype, start, end);
	}
	return req;
}

class BudgetManager {
private:
	struct daily_data {
		double income;
		double spending;
	};
	vector<daily_data> data;

public:
	BudgetManager()	
	: data(MAX_DAYS, {0,0})
	{
	}

	Request::Answer ProcessRequest(Request* req) {
		switch (req->request_type) {
			case Request::Type::EARN:
				return Earn(req->start_date, req->end_date, req->value.value());
			case Request::Type::SPEND:
				return Spend(req->start_date, req->end_date, req->value.value());
			case Request::Type::PAY_TAX:
				return PayTax(req->start_date, req->end_date, req->value.value());
			case Request::Type::COMPUTE_INCOME:
				return ComputeIncome(req->start_date, req->end_date);
		}
		return nullopt;
	}
private:
	Request::Answer Earn(const Date& start_date, 
			const Date& end_date, size_t value) 
	{
		size_t start = start_date.AsDays();
		//cerr << start << endl;
		size_t end = end_date.AsDays() + 1;
		//cerr << end << endl;
		double daily_value = value * 1.0 / (end - start);
		for (size_t day = start; day < end; day++) {
			data[day].income += daily_value;
		}
		return nullopt;
	}

	Request::Answer PayTax(const Date& start_date, 
			const Date& end_date, size_t percentage) 
	{
		size_t start = start_date.AsDays();
		size_t end = end_date.AsDays() + 1;
		for (size_t day = start; day < end; day++) {
			data[day].income *= 1 - percentage / 100.0;
		}
		return nullopt;
	}

	Request::Answer Spend(const Date& start_date, 
			const Date& end_date, size_t value) 
	{
		size_t start = start_date.AsDays();
		//cerr << start << endl;
		size_t end = end_date.AsDays() + 1;
		//cerr << end << endl;
		double daily_value = value * 1.0 / (end - start);
		for (size_t day = start; day < end; day++) {
			data[day].spending += daily_value;
		}
		return nullopt;
	}

	Request::Answer ComputeIncome(const Date& start_date, 
			const Date& end_date) const 
	{
		auto start = start_date.AsDays();
		auto end = end_date.AsDays() + 1;
		//cerr << start << endl;
		//cerr << end << endl;
		double income = 0;
		for (size_t day = start; day < end; day++) {
			income += data[day].income - data[day].spending;
		}
		return income;
	}

};



int main() {
	BudgetManager bm;
	cout.precision(25);
	size_t Q;
	cin >> Q;
	for (size_t i = 0; i < Q; i++) {
		Request::Answer answer = bm.ProcessRequest(ReadRequest(cin).get());
		if (answer.has_value()) {
			cout << answer.value() << endl;
		}
	}
}

