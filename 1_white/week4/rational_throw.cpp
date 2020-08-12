#include <iostream>
#include <exception>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
		Numerator_ = 0;
		Denominator_ = 1;
    }

    Rational(int numerator, int denominator) {
        // Реализуйте конструктор
		if (numerator == 0) {
			Numerator_ = 0;
			Denominator_ = 1;
		} else {
			if (denominator < 0) {
				Numerator_ = -numerator;
				Denominator_ = -denominator;
			} else if (denominator == 0) {
				throw invalid_argument("Invalid argument");
			} else {
				Numerator_ = numerator;
				Denominator_ = denominator;
			}
			auto _gcd = gcd(Numerator_, denominator);
			Numerator_ /= _gcd;
			Denominator_ /= _gcd;
		}
    }

    int Numerator() const {
        // Реализуйте этот метод
		return Numerator_;
    }

    int Denominator() const {
        // Реализуйте этот метод
		return Denominator_;
    }

private:
    // Добавьте поля
	int Numerator_;
	int Denominator_;
};

Rational operator+ (const Rational& lhs, const Rational& rhs) {
	int ln = lhs.Numerator();
	int rn = rhs.Numerator();
	int ld = lhs.Denominator();
	int rd = rhs.Denominator();

	if (ld == rd) {
		return Rational(ln + rn, ld);
	}
	auto _lcm = lcm(ld, rd);
	int lc = _lcm / ld;
	int rc = _lcm / rd;
	return Rational(ln * lc + rn * rc, _lcm);
}

Rational operator- (const Rational& lhs) {
	return Rational(-lhs.Numerator(), lhs.Denominator());
}

Rational operator- (const Rational& lhs, const Rational& rhs) {
	return lhs + (-rhs);
}

bool operator== (const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator()) && 
		(lhs.Denominator() == rhs.Denominator());
}

bool operator!= (const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() != rhs.Numerator()) || 
		(lhs.Denominator() != rhs.Denominator());
}

Rational operator* (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator/ (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(),
			lhs.Denominator() * rhs.Numerator());
}

ostream& operator<< (ostream& s, const Rational& rational) {
	s << rational.Numerator() << "/" << rational.Denominator();
	return s;
}

istream& operator>> (istream& s, Rational& rational) {
	// if string is empty do nothing
	if (s.peek() == EOF) {
		return s;
	}
	int num, den;
	s >> num;
	if (s.peek() == '/') {
		s.ignore(1);
	}
	s >> den;
	rational = Rational(num, den);
	return s;
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
