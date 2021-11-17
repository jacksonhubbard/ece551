#include <cstdlib>
#include <iostream>
#include <string>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (high > low) {
    int mid = (high + low) / 2;
    int value = f->invoke(mid);
    if (value == 0) {
      return mid;
    }
    else if (value > 0) {
      //return binarySearchForZero(f, low, mid);
      high = mid;
    }
    else {  // less than 0
      //return binarySearchForZero(f, mid, high);
      low = mid;
    }
  }
  if (low > 0) {
    return low;
  }
  else {
    return high - 1;
  }
}
