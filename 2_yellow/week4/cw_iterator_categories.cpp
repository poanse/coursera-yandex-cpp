#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(){
	stringstream s {"a b c"};
	istream_iterator<string> start(s);
	istream_iterator<string> end;
	vector<string> strings(start, end);
	cout << *start++ << endl;
	cout << *start++ << endl;
	cout << *start++ << endl;
	cout << *start++ << endl;
	cout << *start++ << endl;
	vector<string> more_strings(start, end);
	cout << more_strings.size();
	//cout << more_strings[0];
}
