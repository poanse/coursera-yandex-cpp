#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

using Tasks = vector<vector<string>>;

class MonthlyTasks {
public:
	MonthlyTasks() {
	 tasks = Tasks(days[current_month]);
	}
	void Next() {
		current_month = ++current_month % 12;
		Tasks new_tasks(days[current_month]);
		for (auto i = 0; i < min(tasks.size(), new_tasks.size()); i++) {
			new_tasks[i] = tasks[i];
		}
		if (new_tasks.size() < tasks.size()) {
			auto& v = *new_tasks.rbegin();
			for (auto i = new_tasks.size(); i < tasks.size(); i++) {
				v.insert(v.end(), tasks[i].begin(), tasks[i].end());
			}
		}
		tasks = move(new_tasks);
	}
	void Dump(int day) const {
		day--;
		auto& t = tasks[day];
		cout << t.size() << ' ';
		if (t.size() == 1) {
			cout << t[0];
		} else if (t.size() >= 2) {
			for (auto it = t.begin(); it != prev(t.end()); it++) {
				cout << *it << ' ';
			}
			cout << *prev(t.end());
		}
		cout << endl;
		//cout << endl;
	}
	void Add(int day, const string& task) {
		day--;
		tasks[day].push_back(task);
	}
	void DoCommand(istringstream& str) {
			string command_name;
			str >> command_name;
			if (command_name == "NEXT") {
				Next();
				return;
			}
			int number;
			str >> number;
			if (command_name == "DUMP") {
				Dump(number);
				return;
			}
			string task;
			str >> task;
			if (command_name == "ADD") {
				Add(number, task);
				return;
			}
			//cerr << "Unknown command" << endl;
	}
private:
	int current_month = 0;
	Tasks tasks;
	vector<int> days = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
};




int main() {
	MonthlyTasks mtasks;
	string command;
	string N;
	getline(cin, N);
	for (auto i = 0; i < stoi(N); i++) {
		getline(cin, command);
		istringstream str(command);
		mtasks.DoCommand(str);
	}
}
