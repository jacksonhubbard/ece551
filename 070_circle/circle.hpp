#include "point.hpp"

class Circle {
 private:
  Point p;
  const double r;

 public:
  Circle(Point point, double rad) : p(point), r(rad) {}

  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
