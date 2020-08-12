#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Log {
	Log(string name) : n(name) {
		cout << "+ " << n << endl;
	}

	~Log() {
		cout << "- " << n << endl;
	}

	string n;
};

struct Fruit {
	Fruit(const string& t) 
		: l(t + " (Fruit)")
		, type(t) {
	}
	int health = 0;
	const string type;
	const Log l;
};

struct Apple : public Fruit {
	Apple() : Fruit("Apple") {
		health = 10;
	} 
};

struct Orange : public Fruit {
	Orange() : Fruit("Orange") {
		health = 5;
	} 
};

class Animal {
public:
	Animal(const string& t = "animal") 
	: type (t) {
	}
	void Eat(const Fruit& f) {
		cout << type << " eats " << f.type << ". " 
			 << f.health << "hp." << endl;
	}

	virtual void Sound() const  = 0;
//protected:
	//string type = "Animal";
private:
	const string type = "Animal";
};

class Cat : public Animal{
public:
	Cat() : Animal("cat") {
	}
	void Sound() const override {
		cout << "meow! " << endl;
	}
};

class Dog : public Animal{
public:
	Dog() : Animal("dog") {
	}
	void Sound() const override {
		cout << "bark! " << endl;
	}
};

class Parrot : public Animal {
public:
	Parrot(const string& name) 
		: Animal("parrot")
		, name_(name) {
	}
	void Sound() const override {
		cout << name_ << " is good!" << endl;
	}

	void Talk() const {
		cout << name_ << " is good!" << endl;
	}
private:
	const string name_;
};

class Horse : public Animal {
public:
	Horse() : Animal("horse"){}
};

void DoMeal(Animal& a, Fruit& f){
	a.Eat(f);
	//a.type += "*";
}

void MakeSound(const Animal& a) {
	a.Sound();
}

int main() {
	Cat c;
	Dog d;
	Parrot p("Polly");
	//Horse h;

	//Apple a;
	//Orange o;

	//c.Eat(a);
	//d.Eat(o);

	shared_ptr<Animal> a;

	//a = make_shared<Cat>();
	//a->Sound();

	vector<shared_ptr<Animal>> animals {
		make_shared<Cat>(),
		make_shared<Dog>(),
		make_shared<Parrot>("Polly")
	};

	for (const auto& a : animals) {
		MakeSound(*a);
	}
	//MakeSound(c);
	//MakeSound(d);
	//MakeSound(p);
	//MakeSound(h);
}
