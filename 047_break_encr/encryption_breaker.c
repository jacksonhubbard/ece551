#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int arrayMax(int * array, int n) {
  if (n < 1) {
    return -1;
  }
  int largestIndex = 0;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[largestIndex]) {
      largestIndex = i;
    }
  }
  return largestIndex;
}

void encryption_breaker(FILE * f) {
  int c;

  int freqs[26] = {0};

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      int offset = c - 97;
      freqs[offset] += 1;
    }
  }

  int indexOfMostFreq = arrayMax(freqs, 26);
  char mostUsedChar = 97 + indexOfMostFreq;

  int offsetMostFreqs = mostUsedChar - 'e';
  if (offsetMostFreqs < 0) {
    offsetMostFreqs = 26 + offsetMostFreqs;
  }
  printf("%d\n", offsetMostFreqs);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: programName fileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  encryption_breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
