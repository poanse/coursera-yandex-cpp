#include <iostream>
#include <string>

using namespace std;

struct Specialization {
	string content;
	explicit Specialization(string s)
	{
		content = s;
	};
};

struct Course {
	string content;
	explicit Course(string s)
	{
		content = s;
	};
};

struct Week {
	string content;
	explicit Week(string s)
	{ 
		content = s;
	};
};


struct LectureTitle {
  string specialization;
  string course;
  string week;
	LectureTitle(Specialization s, Course c, Week w)
		: specialization(s.content)
		, course(c.content)
		, week(w.content)
	{
	}
};

int main() {
	LectureTitle title(
			Specialization("C++"),
			Course("White belt"),
			Week("4th")
	);
}
