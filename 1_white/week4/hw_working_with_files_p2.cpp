#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream file1("input.txt");
	ofstream file2("output.txt");
	char c;
	while(file1.get(c)) {
		file2 << c;
	}
}
