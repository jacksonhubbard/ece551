#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t max = 0;
  size_t curr = 1;
  int prev = array[0];

  if (n == 0) {
    return 0;
  }

  for (int i = 1; i < (int)n; i++) {
    if (array[i] > prev) {
      curr++;
    }
    else {
      if (curr > max) {
        max = curr;
      }
      curr = 1;
    }
    prev = array[i];
  };

  if (curr > max) {
    max = curr;
  }

  return max;
}
