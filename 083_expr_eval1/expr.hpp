#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 protected:
  long number;

 public:
  NumExpression(long num) : number(num) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
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

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
