#include <iostream>
#include <vector>

using namespace std;

vector<int> q;
enum command_codes {WORRY, QUIET, COME_ADD, COME_REMOVE, WORRY_COUNT};

void DoCommand(int code, int number) {
	switch(code) {
		case command_codes::WORRY:
			q[number] = 1;
			break;
		case command_codes::QUIET:
			q[number] = 0;
			break;
		case command_codes::COME_ADD:
			for (; number > 0; number--) {
				q.push_back(0);
			}
			break;
		case command_codes::COME_REMOVE:
			q.erase(q.end() + number, q.end()); // number < 0
			break;
		case command_codes::WORRY_COUNT:
			int count = 0;
			for (auto x : q) {
				if (x == 1) {
					count++;
				}
			}
			cout << count << endl;
			break;
	}
}

int main() {
	int Q;
	cin >> Q;
	for (auto i = 0; i < Q; i++) {
		string command;
		cin >> command;
		if (command == "WORRY_COUNT") {
			DoCommand(command_codes::WORRY_COUNT, 0);
			continue;
		}
		int number;
		cin >> number;
		if (command == "WORRY") {
			DoCommand(command_codes::WORRY, number);
		} else if (command == "QUIET") {
			DoCommand(command_codes::QUIET, number);
		} else if (command == "COME" && number >= 0) {
			DoCommand(command_codes::COME_ADD, number);
		} else if (command == "COME" && number < 0) {
			DoCommand(command_codes::COME_REMOVE, number);
		}
	}
}
