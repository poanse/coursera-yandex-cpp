#include <math.h> 
#include <iostream> 
#include <string> 
#include <memory> 
#include <vector> 
#include <sstream> 
#include <iomanip> 

using namespace std;

const double Pi = 3.14;
const string RECTANGLE_NAME = "RECT";
const string TRIANGLE_NAME = "TRIANGLE";
const string CIRCLE_NAME = "CIRCLE";


class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};


class Circle : public Figure {
private:
	size_t r;
public:
	Circle(size_t _r) 
		: r(_r)
	{
	}
	string Name() const {
		return CIRCLE_NAME;
	}
	double Perimeter() const {
		return 2 * Pi * r;
	}
	double Area() const {
		return Pi * r * r;
	}
};


class Rect : public Figure {
private:
	size_t width;
	size_t height;
public:
	Rect(size_t w, size_t h) 
		: width(w)
		, height(h) 
	{
	}
	string Name() const {
		return RECTANGLE_NAME;
	}
	double Perimeter() const {
		return 2 * (width + height);
	}
	double Area() const {
		return width * height;
	}
};

class Triangle : public Figure {
private:
	size_t a;
	size_t b;
	size_t c;
public:
	Triangle(size_t _a, size_t _b, size_t _c) 
		: a(_a)
		, b(_b) 
		, c(_c) 
	{
	}
	string Name() const {
		return TRIANGLE_NAME;
	}
	double Perimeter() const {
		return a + b + c;
	}
	double Area() const {
		auto p = Perimeter() / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
};


shared_ptr<Figure> CreateFigure(istream& is) {
	string fig;
	is >> fig;
	if (fig == RECTANGLE_NAME) {
		size_t w, h;
		is >> w >> h;
		return make_shared<Rect>(w, h);
	} else if (fig == TRIANGLE_NAME) {
		size_t a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	} else if (fig == CIRCLE_NAME) {
		size_t r;
		is >> r;
		return make_shared<Circle>(r);
	} else {
		return {};
	}
}



int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
