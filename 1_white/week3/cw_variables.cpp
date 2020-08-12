#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	{
		int x = 5;
		{
			cout << x;
		}
		cout << x;
	}
	// variable x is not visible here
	if (true) {
		int x = 5;
	}
	//	cout << x; does not compile!
	string s = "hello";
	{
		string s = "world";
		cout << s << endl;
	}
	cout << s << endl;
}
