#include "circle.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void Circle::move(double dx, double dy) {
  this->p.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double r1 = this->r;
  double r2 = otherCircle.r;

  double x1 = p.getX();
  double x2 = otherCircle.p.getX();

  double y1 = p.getY();
  double y2 = otherCircle.p.getY();

  double area1 = r1 * r1 * 3.1415926535;
  double area2 = r2 * r2 * 3.1415926535;

  double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  if (d > (r1 + r2)) {
    return 0.0;
  }

  if (d <= abs(r1 - r2) && r1 >= r2) {
    return area2;
  }
  else if (d <= abs(r1 - r2) && r1 < r2) {
    return area1;
  }
  else {
    double arg1 = this->r * this->r *
                  acos((d * d + this->r * this->r - otherCircle.r * otherCircle.r) /
                       (2 * d * this->r));
    double arg2 = otherCircle.r * otherCircle.r *
                  acos((d * d - this->r * this->r + otherCircle.r * otherCircle.r) /
                       (2 * d * otherCircle.r));
    double arg3 =
        0.5 * sqrt((d + this->r - otherCircle.r) * (d - this->r + otherCircle.r) *
                   ((-1 * d) + this->r + otherCircle.r) * (d + this->r + otherCircle.r));
    double ans = arg1 + arg2 - arg3;

    return ans;
  }
}
