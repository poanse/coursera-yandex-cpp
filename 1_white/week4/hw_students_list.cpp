#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student{
	string name;
	string surname;
	int day;
	int month;
	int year;
};

class Database{
	public:
		void AddStudent() {
			Student new_student;
			cin >> new_student.name;
			cin >> new_student.surname;
			cin >> new_student.day;
			cin >> new_student.month;
			cin >> new_student.year;
			students.push_back(new_student);
		}

		void PrintName(int K) {
			cout << students[K - 1].name << " " << students[K - 1].surname << endl;
		}

		void PrintDate(int K) {
			cout << students[K - 1].day << ".";
			cout << students[K - 1].month << ".";
			cout << students[K - 1].year << endl;
		}
	private:
		vector<Student> students;
};


int main() {
	int N;
	cin >> N;
	Database data;
	for (int i = 0; i < N; ++i) {
		data.AddStudent();
	}
	int M;
	cin >> M;
	int K;
	string command;
	for (int i = 0; i < M; i++) {
		cin >> command >> K;
		if ((command != "name" && command != "date") || (K > N || K < 1)) {
			cout << "bad request" << endl;
		} else if (command == "name") {
			data.PrintName(K);
		} else if (command == "date") {
			data.PrintDate(K);
		} else {
			cout << "bad request" << endl;
		}
	}
}
