#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

void performTest() {
  run_check(0, 1, 0);
  run_check(1, 2, 1);
  run_check(2, 2, 4);
  run_check(2, 2.0, 4.0);
  run_check(-2, 2, 4);
  run_check(1, -1, 1);
  run_check(2, 10, 1024);
  run_check(100, 2, 10000);
  run_check(-1, 2, 1);
  run_check(-1, 3, -1);
  run_check(2, 20, 1048576);
  run_check(1, 5, 1);
  run_check(0, 0, 1);
}

int main() {
  performTest();
  return EXIT_SUCCESS;
}
