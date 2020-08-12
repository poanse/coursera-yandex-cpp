#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

struct Duration {
	int hour;
	int min;

	Duration(int h = 0, int m = 0) {
		hour = h;
		min = m;
	}
};

//Duration ReadDuration(istream& stream) {
//	int h = 0;
//	int m = 0;
//	stream >> h;
//	stream.ignore(1);
//	stream >> m;
//	return Duration {h, m};
//}

istream& operator>>(istream& stream, Duration& duration) {
	stream >> duration.hour;
	stream.ignore(1);
	stream >> duration.min;
	return stream;
}


ostream& operator<<(ostream& stream, const Duration& duration) {
	stream << setfill('0');
	stream << setw(2) << duration.hour << ":"
			<< setw(2) << duration.min;
	return stream;
}

int main() {
	stringstream dur_ss("01:50");
	Duration dur1;
	//PrintDuration(cout, dur1);
	//cout << endl;
	dur_ss >> dur1;
	cout << dur1 << endl;
	//operator<<(operator<<(cout, "hello"), " world");
}
