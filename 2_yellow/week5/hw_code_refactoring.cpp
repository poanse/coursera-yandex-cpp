#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person {
public:
		Person(string name, string _occupation) 
				: Name(move(name)) 
				, occupation(move(_occupation))
		{
		}

		virtual void Walk(const string& destination) const {
				cout << occupation << ": " << Name 
					<< " walks to: " << destination << endl;
		}
public:
		const string Name;
		const string occupation;
};

class Student : public Person {
public:
    Student(string name, string favouriteSong) 
				: Person(move(name), "Student")
				, FavouriteSong(move(favouriteSong))
		{
    }

    void Learn() const {
        cout << occupation << ": " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const {
				Person::Walk(destination);
				SingSong();
    }

    void SingSong() const {
        cout << occupation << ": " << Name 
					<< " sings a song: " << FavouriteSong << endl;
    }

private:
		const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(string name, string subject)
				: Person(move(name), "Teacher")
				, Subject(move(subject)) 
		{
    }

    void Teach() const {
        cout << occupation << ": " << Name << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(string name) 
		: Person(move(name), "Policeman")
		{
    }

		void Check(const Person *p) const {
        cout << occupation << ": " << Name << " checks " 
					<< p->occupation << ". " << p->occupation 
					<< "'s name is: " << p->Name << endl;
		}
};

void VisitPlaces(const Person *p, const vector<string>& places) {
    for (const auto& place : places) {
        p->Walk(place);
    }
}

int main() {
		auto t = make_shared<Teacher>("Jim", "Math");
		auto s = make_shared<Student>("Ann", "We will rock you");
		auto p = make_shared<Policeman>("Bob");

    VisitPlaces(t.get(), {"Moscow", "London"});
    p->Check(s.get());
    VisitPlaces(s.get(), {"Moscow", "London"});
    return 0;
}
