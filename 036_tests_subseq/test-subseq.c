#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  size_t ans = maxSeq(array, n);

  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

void performTest() {
  int arr[] = {1, 2, 3};
  int * p = arr;
  run_check(p, 3, 3);

  int arr2[] = {1, 1, 2};
  p = arr2;
  run_check(p, 3, 2);

  int arr3[] = {4, 3, 1, 2, 0, 1, 2, 3};
  p = arr3;
  run_check(p, 8, 4);

  int arr4[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  p = arr4;
  run_check(p, 10, 4);

  int arr5[3] = {0};
  p = arr5;
  run_check(p, 3, 1);

  int arr6[] = {-5, -4, -3, 0, 2, 3, 4, 5};
  p = arr6;
  run_check(p, 8, 8);

  int arr7[] = {5, 4, 3, 2, 1};
  p = arr7;
  run_check(p, 5, 1);

  int arr8[] = {1, 2, 3, 3, 3, 3};
  p = arr8;
  run_check(p, 6, 3);

  int arr9[] = {1};
  p = arr9;
  run_check(p, 1, 1);

  int arr10[] = {1, 2, 3, -4, -3, -2, -1, 9, 10, 11, 10, 3, 4, 5, 6};
  p = arr10;
  run_check(p, 15, 7);

  run_check(NULL, 0, 0);
}

int main() {
  performTest();
  return EXIT_SUCCESS;
}