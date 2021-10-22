#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[n];
}

IntArray::IntArray(const IntArray & rhs) {
  data = new int[rhs.numElements];
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
  numElements = rhs.numElements;
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  data = rhs.data;
  numElements = rhs.numElements;
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  assert(index >= 0);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index < numElements);
  assert(index >= 0);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements == rhs.numElements) {
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements == rhs.numElements) {
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) {
        return true;
      }
    }
    return false;
  }
  return true;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[rhs.size() - 1] << "}";
  return s;
}
