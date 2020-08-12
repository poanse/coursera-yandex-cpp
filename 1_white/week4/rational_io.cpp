#include <iostream>
#include <sstream>
#include "rational.h"
using namespace std;

// Вставьте сюда реализацию operator == для класса Rational из второй части

// Реализуйте для класса Rational операторы << и >>

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }
    {
        istringstream input("5/7");
        Rational r1, r2;
				int a = 10;
        input >> r1 >> r2 >> a;
				bool equal = r2 == Rational(0, 1);
				//cout << "a equals " << a << endl;
        if (!equal) {
            cout << "Read from empty stream works incorrectly: 0/1 vs " << r2 << endl;
            return 5;
        }
    }

    //{
        //istringstream input("5f/ 2 5/4");
        //Rational r1, r2;
        //input >> r1 >> r2;
				//bool equal = r1 == Rational(0, 1) && r2 == Rational(5, 4);
        //if (!equal) {
            //cout << "Expected: 0/1 and 5/4, read: " << r1 << " and " << r2 << endl;
            //return 6;
        //}
    //}

    cout << "OK" << endl;
    return 0;
}
