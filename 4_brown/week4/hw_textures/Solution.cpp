#include "Common.h"
#include <unordered_set>
#include <algorithm>
using namespace std;

const char DEFAULT_SYMBOL = '.';

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

bool operator== (const Point& lhs, const Point& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

struct Hasher {
	int operator()(const Point p) const {
		auto h = hash<int>();
		int output = 17;
		output *= h(p.x) + 1;
		output *= h(p.y) + 1;
		return output;
	}
};

class Rectangle : public IShape {
protected:
	Point position;
	Size size;
	shared_ptr<ITexture> texture;
public:
	virtual void SetPosition(Point p) override {
		position = move(p);
	}
	virtual Point GetPosition() const override {
		return position;
	}

	virtual void SetSize(Size s) override {
		size = move(s);
	}
	virtual Size GetSize() const override {
		return size;
	}

	virtual void SetTexture(shared_ptr<ITexture> t) override {
		texture = move(t);
	}
	virtual ITexture* GetTexture() const override {
		return texture.get();
	}

	virtual unique_ptr<IShape> Clone() const override {
		auto clone = make_unique<Rectangle>();
		clone->SetPosition(position);
		clone->SetSize(size);
		clone->SetTexture(texture);
		return clone;
	}

	// Рисует фигуру на указанном изображении
	virtual void Draw(Image& img) const override {
		int xmax = min(position.x + size.width, (int)img[0].size());
		int ymax = min(position.y + size.height, (int)img.size());
		unordered_set<Point, Hasher> points;
		for (auto i = 0; i + position.y < ymax; i++) {
			for (auto j = 0; j + position.x < xmax; j++) {
				points.insert({j, i});
			}
		}

		Image texture_img;
		Size texture_size;
		if (texture) {
			texture_img = texture->GetImage();
			texture_size = texture->GetSize();
		}
		for (const auto& point : points) {
			char symbol;
			// if texture contains a point -> get pixel from texture
			if (texture && 
					texture_size.height > point.y && 
					texture_size.width > point.x) {
				symbol = texture_img[point.y][point.x];
			} else {
				// otherwise use default symbol
				symbol = DEFAULT_SYMBOL;
			}
			// draw it on img
			img[point.y + position.y][point.x + position.x] = symbol;
		}
	}
};

class Ellipse : public Rectangle {
	virtual void Draw(Image& img) const override {
		int xmax = min(position.x + size.width, (int)img[0].size());
		int ymax = min(position.y + size.height, (int)img.size());
		unordered_set<Point, Hasher> points;
		for (auto i = 0; i + position.y < ymax; i++) {
			for (auto j = 0; j + position.x < xmax; j++) {
				Point p {j, i};
				if (IsPointInEllipse(p, size)) {
					points.insert(p);
				}
			}
		}

		Image texture_img;
		Size texture_size;
		if (texture) {
			texture_img = texture->GetImage();
			texture_size = texture->GetSize();
		}
		for (const auto& point : points) {
			char symbol;
			// if texture contains a point -> get pixel from texture
			if (texture && 
					texture_size.height > point.y && 
					texture_size.width > point.x) {
				symbol = texture_img[point.y][point.x];
			} else {
				// otherwise use default symbol
				symbol = DEFAULT_SYMBOL;
			}
			// draw it on img
			img[point.y + position.y][point.x + position.x] = symbol;
		}
	}

};



// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	if (shape_type == ShapeType::Rectangle) {
		return make_unique<Rectangle>();
	} else if (shape_type == ShapeType::Ellipse) {
		return make_unique<Ellipse>();
	}
	return make_unique<Rectangle>();
}
