#include "circle.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Circle::move(double dx, double dy) {
  this->p.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double d = abs(p.getX() - otherCircle.p.getX());

  double arg1 = this->r * this->r *
                acos((d * d + this->r * this->r - otherCircle.r * otherCircle.r) /
                     (2 * d * this->r));
  double arg2 = otherCircle.r * otherCircle.r *
                acos((d * d + this->r * this->r + otherCircle.r * otherCircle.r) /
                     (2 * d * otherCircle.r));
  double arg3 =
      0.5 * sqrt((d + this->r - otherCircle.r) * (d - this->r + otherCircle.r) *
                 ((-1 * d) + this->r + otherCircle.r) * (d + this->r + otherCircle.r));
  return arg1 + arg2 - arg3;
}
