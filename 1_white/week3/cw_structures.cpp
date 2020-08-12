#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Lecture {
	string title;
	int duration;
	string author;
}

void PrintLecture(const Lecture& lecture) {
	cout <<
		"Title: " << lecture.title <<
		", duration: " << lecture.duration <<
		", author: " << lecture.author << endl;
}

void PrintCourse(const vector<Lecture>& lectures) {
	for (const Lecture& lecture : lectures) {
		PrintLecture(lecture);
	}
}

int main() {
	Lecture	lecture1;
	lecture1.title = "OOP;
	lecture1.duration = 5400;
	lecture1.author = "Anton;

	Lecture lecture2 = {"OOP", 5400, "Anton"};
	
	PrintLecture({"OOP", 5400, "Anton"});
}
