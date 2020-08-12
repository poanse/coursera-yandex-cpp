#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Person {
	string name;
	string surname;
	int age;
};

vector<Person> GetMoscowPopulation();

void PrintPopulationSize(const vector<Person>& p) {
	cout << "There are " << p.size() << " people in Moscow" << endl;
}

int main() {
	vector<Person> people = GetMoscowPopulation();
	PrintPopulationSize(people);
}
