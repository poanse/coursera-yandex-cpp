#pragma once
#include "date.h"

#include <memory>
#include <string>

enum class LogicalOperation {
	And,
	Or
};

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};


class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class LogicalOperationNode : public Node{
private:
	const LogicalOperation op_;
	const std::shared_ptr<Node> left_;
	const std::shared_ptr<Node> right_;
public:
	LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> left, 
			std::shared_ptr<Node> right);
	bool Evaluate(const Date& date, const std::string& event) const override;
};


class DateComparisonNode : public Node{
private:
	const Comparison cmp_;
	const Date date_;
public:
	DateComparisonNode(Comparison cmp, Date date);
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class EventComparisonNode : public Node{
private:
	const Comparison cmp_;
	const std::string event_;
public:
	EventComparisonNode(Comparison cmp, std::string event);
	bool Evaluate(const Date& date, const std::string& event) const override;
};
