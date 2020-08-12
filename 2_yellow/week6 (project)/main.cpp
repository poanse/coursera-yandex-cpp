#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "test_db.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
  // Реализуйте эту функцию
	string event;
	is >> ws;
	getline(is, event);
	if (!is) {
		throw invalid_argument("ParseEvent failed");
	}
	return event;
}

void TestAll();

void Run(istream& cin, ostream& cout) {

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
}

int main() {
	TestAll();
	Run(cin, cout);
  return 0;
}

void TestParseEvent() {
	{
		istringstream is("event");
		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
	}
	{
		istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
	}
	{
		istringstream is("  first event  \n  second event");
		vector<string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
	}
}

void TestDb1(){
	{
		istringstream is("");
		ostringstream os("");
		Run(is, os);
		string exprected = "";
		AssertEqual(os.str(), exprected, "123");
	}
	{
		istringstream is(R"(Add 2017-06-01 1st of June
Add 2017-07-08 8th of July
Add 2017-07-08 Someone's birthday
Del date == 2017-07-08
)");
		ostringstream os("");
		Run(is, os);
		string exprected = "Removed 2 entries\n";
		AssertEqual(os.str(), exprected, "123");
	}
	{
		istringstream is(R"(Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-1-1 New Year
Add 2017-1-1 New Year
Print
)");
		ostringstream os("");
		Run(is, os);
		string exprected = "2017-01-01 Holiday\n"
		"2017-01-01 New Year\n"
		"2017-03-08 Holiday\n";
		AssertEqual(os.str(), exprected, "123");
	}
	{
		istringstream is(
"Add 2017-01-01 Holiday\n"
"Add 2017-03-08 Holiday\n"
"Add 2017-01-01 New Year\n"
"Find event != \"working day\"\n"
"Add 2017-05-09 Holiday\n");
		ostringstream os("");
		Run(is, os);
		string exprected = 
	"2017-01-01 Holiday\n"
	"2017-01-01 New Year\n"
	"2017-03-08 Holiday\n"
	"Found 3 entries\n";
		AssertEqual(os.str(), exprected, "123");
	}
	{
		istringstream is(
R"(Add 2017-01-01 New Year
Add 2017-03-08 Holiday
Add 2017-01-01 Holiday
Last 2016-12-31
Last 2017-01-01
Last 2017-06-01
Add 2017-05-09 Holiday
)");
		ostringstream os("");
		Run(is, os);
		string exprected = 
R"(No entries
2017-01-01 Holiday
2017-03-08 Holiday
)";
		AssertEqual(os.str(), exprected, "123");
	}
	{
		istringstream is(
R"(Add 2017-11-21 Tuesday
Add 2017-11-20 Monday
Add 2017-11-21 Weekly meeting
Print
Find event != "Weekly meeting"
Last 2017-11-30
Del date > 2017-11-20
Last 2017-11-30
Last 2017-11-01
)");
		ostringstream os("");
		Run(is, os);
		string exprected = 
R"(2017-11-20 Monday
2017-11-21 Tuesday
2017-11-21 Weekly meeting
2017-11-20 Monday
2017-11-21 Tuesday
Found 2 entries
2017-11-21 Weekly meeting
Removed 2 entries
2017-11-20 Monday
No entries
)";
		AssertEqual(os.str(), exprected, "123");
	}
	{
		istringstream is(
R"(Add 2017-11-21 Tuesday
Add 2017-11-20 Monday
Add 2017-11-20 Monday
Add 2017-11-21 Weekly meeting
Print
Del event == "Monday"
Add 2017-11-20 Monday
Find event != "Weekly meeting"
Last 2017-11-21
Last 2017-11-22
Last 2015-11-22
)");
		ostringstream os("");
		Run(is, os);
		string exprected = 
R"(2017-11-20 Monday
2017-11-21 Tuesday
2017-11-21 Weekly meeting
Removed 1 entries
2017-11-20 Monday
2017-11-21 Tuesday
Found 2 entries
2017-11-21 Weekly meeting
2017-11-21 Weekly meeting
No entries
)";
		AssertEqual(os.str(), exprected, "123");
	}
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestParseCondition, "TestParseCondition");
	tr.RunTest(TestDb1, "testdb1");  
	tr.RunTest(TestEmptyNode, "Тест 2 из Coursera");
	tr.RunTest(TestDbAdd, "Тест 3(1) из Coursera");
	tr.RunTest(TestDbFind, "Тест 3(2) из Coursera");
	tr.RunTest(TestDbLast, "Тест 3(3) из Coursera");
	tr.RunTest(TestDbRemoveIf, "Тест 3(4) из Coursera");
	tr.RunTest(TestInsertionOrder, "Тест на порядок вывода");
	tr.RunTest(TestsMyCustom, "Мои тесты");
	tr.RunTest(TestDatabase, "Тест базы данных с GitHub");
}




