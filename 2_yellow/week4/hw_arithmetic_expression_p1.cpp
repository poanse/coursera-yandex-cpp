#include <string>
#include <iostream>

using namespace std;

class Expression {
public:
	string content;
	Expression(const string& str) :content(str) 
	{
	}

	void Step(string str) {
		content = "(" + move(content) + ") " + str;
	}

};


int main() {
	string str;
	size_t N;
	getline(cin, str);
	Expression exp(str);
	cin >> N;
	cin.ignore(1);
	for (auto i = 0; i < N; i++) {
		getline(cin, str);
		exp.Step(move(str));
	}
	cout << exp.content << endl;
}
