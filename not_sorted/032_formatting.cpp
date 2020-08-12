#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


void Print(const vector<string>& names, const vector<double>& values, int width) {
	for (const auto& value : names) {
		cout << setw(width) << value << " ";
	}
	cout << endl;
	cout << fixed << setprecision(2);
	for (const auto& value : values) {
		cout << setw(width) << value << " ";
	}
	cout << endl;
	

}


int main() {
	vector<string> names = {"a", "b", "c"};
	vector<double> values = {5, 0.01, 0.00000005};
	cout << setfill('.');
	cout << left;
	Print(names, values, 10);
}
