#include <iostream>

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
		//type = "apple";
	} 
	//Log l = Log("Apple");
};

//struct Orange : public Fruit {
	//Orange(){
		//health = 5;
		//type = "orange";
	//}
//};

class Animal {
public:
	Animal(const string& t = "animal") 
	: type (t) {
	}
	void Eat(const Fruit& f) {
		cout << type << " eats " << f.type << ". " 
			 << f.health << "hp." << endl;
	}
//protected:
	//string type = "Animal";
	const string type = "Animal";
};

class Cat : public Animal{
public:
	Cat() : Animal("cat") {
	}
	void Meow() const {
		cout << "meow! " << endl;
	}
};

//class Dog : public Animal{
//public:
	//Dog() {
		//type = "Dog";
	//}
//};

void DoMeal(Animal& a, Fruit& f){
	a.Eat(f);
	//a.type += "*";
}

int main() {
	Cat c;
	c.Meow();
	Apple a;
	c.Eat(a);
	//Orange o;
	//c.Eat(o);
	//Dog dog;
	//dog.Eat(a);
	//DoMeal(dog, a);
}
