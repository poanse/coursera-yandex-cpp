#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void ReadAll(const string& path) {
	ifstream input(path);
	if (input) {
		string line;
		while (getline(input, line)) {
			cout << line << endl;
		}
	}
}


int main() {
	//ifstream input("10_if.cpp");
	//string line;
	//if (input) {
	//	while (getline(input, line)) {
	//		cout << line << endl;
	//	}
	//} else {
	//	cout << "no such file" << endl;
	//}
	//
	//vector<string> lines;
	//string tmp;
	//int i = 0;
	//while (input) {
	//	getline(input, tmp, '{');
	//	lines.push_back(tmp);
	//	i++;
	//}
	//for (auto& line : lines) {
	//	cout << line << endl;
	//}

	// write into file
	const string path = "output.txt";
	ofstream output(path, ios::app);
	output << "hello" << endl;
	ReadAll(path);
}
