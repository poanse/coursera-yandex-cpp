#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, 
		std::shared_ptr<Node> left, std::shared_ptr<Node> right) 
	: op_(op)
	, left_(move(left))
	, right_(move(right))
{
}

bool LogicalOperationNode::Evaluate(const Date& date, 
		const std::string& event) const
{
	switch (op_) {
		case LogicalOperation::And:
			return left_->Evaluate(date, event) 
				&&  right_->Evaluate(date, event);
		case LogicalOperation::Or:
			return left_->Evaluate(date, event) 
				||  right_->Evaluate(date, event);
	}
	throw std::logic_error("Invalid logical operation value");
}


namespace ComparisonNode {
	template <typename T>
	bool Compare(Comparison cmp, const T& var, const T& value) {
		switch (cmp) {
			case Comparison::Less:
				return var < value;
			case Comparison::LessOrEqual:
				return var <= value;
			case Comparison::Greater:
				return var > value;
			case Comparison::GreaterOrEqual:
				return var >= value;
			case Comparison::Equal:
				return var == value;
			case Comparison::NotEqual:
				return var != value;
		}
		throw std::invalid_argument("Invalid comparison value");
	}
}


DateComparisonNode::DateComparisonNode(Comparison cmp, Date date)
	: cmp_(cmp)
	, date_(date)
{
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
	return ComparisonNode::Compare(cmp_, date, date_);
}


EventComparisonNode::EventComparisonNode(Comparison cmp, std::string event)
	: cmp_(cmp)
	, event_(event)
{
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
	return ComparisonNode::Compare(cmp_, event, event_);
}
