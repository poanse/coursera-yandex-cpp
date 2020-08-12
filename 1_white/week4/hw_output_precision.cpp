#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
	const string path = "input.txt";
	ifstream input(path);
	cout << fixed << setprecision(3);
	while (input) {
		double value;
		//getline(input, value);
		if (input >> value) {
			cout << value << endl;
		}
	}
}
