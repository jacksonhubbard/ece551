#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 protected:
  long number;

  virtual std::string toString() const { return std::to_string(number); }
};

class PlusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * arg1, Expression * arg2) : lhs(arg1), rhs(arg2) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }
};
