#include <iostream>
#include <vector>
using namespace std;

void PrintVector(const vector<bool>& v) {
	int i = 0;
	for (auto s : v) {
		cout << i << ":" << s << endl;
		++i;
	}
}

int main() {
	/*
	vector<int> days_in_months = {31, 28, 31, 30, 30};
	if (true) {
		// if year is leap
		days_in_months[1]++;
	}
	PrintVector(days_in_months);
	*/
	vector<bool> is_holiday(28, false);
	is_holiday[22] = true;
	PrintVector(is_holiday);

	is_holiday.assign(31, false);
	is_holiday[7] = true;
	PrintVector(is_holiday);

}
