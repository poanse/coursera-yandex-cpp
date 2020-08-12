#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};

istream& operator>> (istream& is, Email& email) {
	getline(is, email.from);
	getline(is, email.to);
	getline(is, email.body);
	return is;
}

ostream& operator<< (ostream& os, Email& email) {
	os << email.from << '\n';
	os << email.to << '\n';
	os << email.body << '\n';
	return os;
}


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const {
		_next->Process(move(email));
	}

public:
  void SetNext(unique_ptr<Worker> next) {
		_next = move(next);
	}

private:
	unique_ptr<Worker> _next;
};


class Reader : public Worker {
public:
  // реализуйте класс
	Reader(istream& is) 
		:_is(is) 
	{
	}

	virtual void Run() {
		Email tmp;
		while (_is >> tmp) {
			auto email = make_unique<Email>();
			*email = move(tmp);
			PassOn(move(email));
		}
	}

	virtual void Process(unique_ptr<Email> email) override {}

private:
	istream& _is;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;
	Filter(Function f) 
		: func(f) 
	{
	}

  virtual void Process(unique_ptr<Email> email) override {
		//cerr << "Filter process" << endl;
		if (func(*email)) {
			PassOn(move(email));
		}
	}

public:
  // реализуйте класс
	Function func;
};


class Copier : public Worker {
public:
  // реализуйте класс
	Copier(string to) 
		: _to(to) 
	{
	}

	virtual void Process(unique_ptr<Email> email) override {
		//cerr << "Copier process" << endl;
		string to = email->to;
		if (_to != email->to) {
			auto email_copy = make_unique<Email>();
			*email_copy = *email;
			email_copy->to = _to;
			PassOn(move(email));
			PassOn(move(email_copy));
			return;
		}
		PassOn(move(email));
	}

private:
	string _to;
};


class Sender : public Worker {
public:
  // реализуйте класс
	Sender(ostream& os) 
		: _os(os) 
	{
	}

	void Process(unique_ptr<Email> email) {
		//cerr << "Sender process" << endl;
		_os << *email;
		//cerr << "email sent" << endl;
	}


private:
		ostream& _os;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in) 
	{
		reader = make_unique<Reader>(in);
		current = reader.get();
	}

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter) {
		auto filt = make_unique<Filter>(filter);
		Worker *new_current = filt.get();
		current->SetNext(move(filt));
		current = new_current;
		return *this;
	}

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient) {
		auto copier = make_unique<Copier>(recipient);
		Worker *new_current = copier.get();
		current->SetNext(move(copier));
		current = new_current;
		return *this;
	}

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out) {
		auto sender = make_unique<Sender>(out);
		auto new_current = sender.get();
		current->SetNext(move(sender));
		current = new_current;
		return *this;
	}

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build() {
		return move(reader);
	}
private:
	unique_ptr<Worker> reader;
	Worker *current;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

	//cerr << "Pipeline built" << endl;
  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
