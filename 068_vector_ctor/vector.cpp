#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
#include <stdio.h>
#include <stdlib.h>

double Vector2D::getMagnitude() const {
  return std::sqrt(this->x * this->x + this->y * this->y);
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  double x = this->x + rhs.x;
  double y = this->y + rhs.y;
  Vector2D ans;
  //Vector2D * ans = new Vector2D(x, y);
  ans.initVector(x, y);
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  static Vector2D ans;
  ans = operator+(rhs);
  *this = ans;
  return ans;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return this->x * rhs.x + this->y * rhs.y;
}

void Vector2D::print() const {
  std::printf("<%.2f, %.2f>", this->x, this->y);
}
