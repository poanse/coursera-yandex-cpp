#include <iostream>
#include <string>
//#include <algorithm>
//#include <vector>
using namespace std;

int main() {
	string str;
	cin >> str;
	int result = -2;
	for (auto i = 0; i < str.size(); i++) {
		if (str[i] == 'f') {
			if (result == -1) {
				result = i;
				break;
			}
			result += 1;
		}
	}
	cout << result;

}
