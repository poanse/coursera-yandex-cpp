#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

namespace expression {
	class Value : public Expression {
	private:
		int _value;
	public:
		Value(int value) 
			: _value(value)
		{
		}
		
		virtual int Evaluate() const {
			return _value;
		}

		virtual std::string ToString() const {
			return to_string(_value);
		}
	};

	class Sum : public Expression  {
	private:
		ExpressionPtr _left;
		ExpressionPtr _right;
	public:
		Sum(ExpressionPtr& left, ExpressionPtr& right)
			: _left(move(left))
			, _right(move(right))
		{
		}

		virtual int Evaluate() const {
			return _left->Evaluate() + _right->Evaluate();
		}

		virtual std::string ToString() const {
			return "(" + _left->ToString() + ")" + "+" + 
				"(" + _right->ToString() + ")";
		}
	};

	class Product : public Expression  {
	private:
		ExpressionPtr _left;
		ExpressionPtr _right;
	public:
		Product(ExpressionPtr& left, ExpressionPtr& right)
			: _left(move(left))
			, _right(move(right))
		{
		}

		virtual int Evaluate() const {
			return _left->Evaluate() * _right->Evaluate();
		}

		virtual std::string ToString() const {
			return "(" + _left->ToString() + ")" + "*" + 
				"(" + _right->ToString() + ")";
		}
	};
}

ExpressionPtr Value(int value) {
	return make_unique<expression::Value>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
	return make_unique<expression::Sum>(left, right);
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
	return make_unique<expression::Product>(left, right);
}

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}
