#include <string>
#include <iostream>
#include <map>
#include <deque>

using namespace std;

const map<char, int> priority = {
	{'*' , 1},
	{'/' , 1},
};

class Expression {
public:
	//string content;
	deque<char> content;
	int last_op_priority;

	Expression(string str) 
		: content(str.begin(), str.end())
		, last_op_priority(1)
	{
	}

	void Step(string str) {
		int current_priority = 
			priority.count(str[0]) ? 1 : 0;
		if (current_priority > last_op_priority) {
			content.push_front('(');
			content.push_back(')');
			content.push_back(' ');
			for (auto ch : str) {
				content.push_back(ch);
			}
			//content = "(" + content + ") " + move(str);
		} else {
			content.push_back(' ');
			for (auto ch : str) {
				content.push_back(ch);
			}
			//content += ' ' + move(str);
		}
		last_op_priority = current_priority;
	}

	void Print() {
		for (auto x : content) {
			cout << x;
		}
	}

};


int main() {
	string str;
	size_t N;
	getline(cin, str);
	Expression exp(move(str));
	cin >> N;
	cin.ignore(1);
	for (auto i = 0; i < N; i++) {
		getline(cin, str);
		exp.Step(move(str));
	}
	exp.Print();
	cout << endl;
}
