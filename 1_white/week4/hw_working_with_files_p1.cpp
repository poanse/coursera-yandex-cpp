#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream file1("input.txt");
	char c;
	while(file1.get(c)) {
		cout << c;
	}
}
