#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
	ifstream file("input.txt");
	int N, M;
	file >> N >> M;
	char delim = ',';
	int number;
	for (auto row = 0; row < N; row++) {
		for (auto col = 0; col < M; col++) {
			file >> number;
			cout << setw(10) << number;
			if (file.peek() == delim || file.peek() == '\n'){
				file.get();
			}
			if (col < M - 1){
				cout << ' ';
			}
		}
		cout <<  '\n';
	}
}

