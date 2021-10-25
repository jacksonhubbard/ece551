#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}
IntArray::IntArray(int n) {
  numElements = n;
  if (n >= 0) {
    data = new int[n]();
  }
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
  delete[] data;
  data = new int[rhs.numElements];
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs[i];
  }
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
      if (data[i] != rhs[i]) {
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
  if (rhs.size() != 0) {
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "}";
  }
  return s;
}
