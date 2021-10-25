#include "IntMatrix.h"

IntMatrix::IntMatrix() {
  numRows = 0;
  numColumns = 0;
  rows = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;

  rows = new IntArray *[rhs.numRows];
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    delete[] rows;
    rows = new IntArray *[rhs.numRows];
    //for (int i = 0; i < rhs.numRows; i++) {
    //IntArray currRow = IntArray(rhs.numColumns);
    //rows[i] = &currRow;
    //rows[i] = new IntArray(rhs.numColumns);
    //}
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    //std::cout << numRows << ", " << numColumns << std::endl;
    for (int i = 0; i < numRows; i++) {
      //std::cout << i << std::endl;
      rows[i] = new IntArray(rhs[i]);
      //std::cout << i << std::endl;
    }
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows == rhs.numRows && numColumns == rhs.numColumns) {
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if ((*this)[i][j] != rhs[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  else {
    return false;
  }
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(numRows, numColumns);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      //std::cout << i << ", " << j << std::endl;
      ans[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  IntArray a;
  s << "{";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << "\n";
  }
  if (rhs.getRows() != 0) {
    s << rhs[rhs.getRows() - 1];
    s << "}";
  }
  else {
    s << "}";
  }
  return s;
}
