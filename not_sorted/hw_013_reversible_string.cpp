#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class ReversibleString{
public:
	// constructors
	ReversibleString(const string& s) {
		str = s;
	}
	ReversibleString() {
		str = "";
	}
	// methods
	void Reverse() {
		/*
		int n = str.size();
		for (int i = 0; i < n / 2; ++i) {
			char tmp = str[i];
			str[i] = str[n - i - 1];
			str[n - i - 1] = tmp;
		*/
		reverse(begin(str), end(str));
	}
	string ToString() const{
		return str;
	}
private:
	string str;
};



int main() {
	ReversibleString s("live");
	s.Reverse();
	cout << s.ToString() << endl;

	ReversibleString empty;
	cout << empty.ToString() << endl;

}
