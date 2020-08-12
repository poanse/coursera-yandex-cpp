#include <iostream>

using namespace std;

class Animal {
public:
    // ваш код
		Animal(string name) : Name(move(name)) 
	  {}

    const string Name;
};


class Dog : public Animal{
public:
    // ваш код
		Dog(string name) : Animal(move(name))
		{
		}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
	Dog d("kitty");
	d.Bark();
}
