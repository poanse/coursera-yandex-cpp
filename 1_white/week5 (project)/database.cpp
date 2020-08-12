#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <set>
using namespace std;

size_t StringCount(const string& str, char ch) {
	size_t counter = 0;
	for (const char& c : str) {
		if (c == ch) {
			counter++;
		}
	}
	return counter;
}

class Date {
public:
	Date() {};
	Date(int y, int m, int d) {
		year = y;
		if (m < 1 || m > 12) {
			throw invalid_argument("Month value is invalid: " + to_string(m));
		}
		if (d < 1 || d > 31) {
			throw invalid_argument("Day value is invalid: " + to_string(d));
		}
		month = m;
		day = d;
	}

	Date(const string& str) {
		stringstream sstream(str);
		char ch1, ch2;
		int y, m, d;
		sstream >> y >> ch1 >> m >> ch2 >> d;;
		if (sstream && ch1 == '-' && ch2 == '-' && sstream.peek() == EOF) {
			*this = Date(y, m, d);
		} else {
			throw invalid_argument("Wrong date format: " + str);
		}
	}
	int GetYear() const {return year;}
	int GetMonth() const {return month;}
	int GetDay() const {return day;}
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) {
		return lhs.GetYear() < rhs.GetYear();
	}
	if (lhs.GetMonth() != rhs.GetMonth()) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetDay() < rhs.GetDay();
}

ostream& operator<< (ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.GetYear() << '-' 
		<< setw(2) << setfill('0') << date.GetMonth() << '-'
		<< setw(2) << setfill('0') << date.GetDay();
	return os;
}

istream& operator>> (istream& is, Date& date) {
	string date_string {""};
	while (is.peek() == ' ') {
		is.get();
	}
	while (is.peek() != ' ' && is.peek() != '\n' && is.peek() != EOF) {
		date_string += is.get();
	}
	date = Date(date_string);
	return is;
}

class Database{
public:
	void AddEvent(const Date& date, const string& event) {
		data[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		if (data[date].count(event)) {
			data[date].erase(event);
			cout << "Deleted successfully\n";
			return true;
		}
		cout << "Event not found\n";
		return false;
	}
	int DeleteDate(const Date& date) {
		int n = data[date].size();
		if (n) {
			data.erase(date);
		}
		cout << "Deleted " << n << " events\n";
		return n;
	}
	void Find(const Date& date) const {
		if (data.count(date)) {
			for (const auto& event : data.at(date)) {
				cout << event << '\n';
			}
		}
	}
	void Print() const {
		for (auto& [date, events] : data) {
			for (auto& event : events) {
				cout << date << ' ' << event << '\n';
			}
		}
	}
	void DoCommand(const string& input) {
		if (input == "") {
			return;
		}
		stringstream stream(input);
		string command, event;
		Date date;
		stream >> command;
		try {
			if (command == "Add") {
				stream >> date >> event;
				AddEvent(date, event);
			} else if (command == "Find") {
				stream >> date;
				if (stream.peek() == EOF) {
					Find(date);
				}
			} else if (command == "Print") {
				Print();
			} else if (command == "Del") {
				stream >> date;
				if (stream.peek() == EOF) {
					DeleteDate(date);
				} else {
					stream >> event;
					DeleteEvent(date, event);
				}
			} else {
				cout << "Unknown command: " << command << endl;
			}
		} catch (exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}
private:
	map<Date, set<string>> data;
};


int main() {
	Database db;
	string command;
	while (getline(cin, command)) {
		db.DoCommand(command);
	}
	return 0;
}
