#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void parseFile(FILE * f) {
  int c;
  int foundStartUnderscore = 0;  // flag to indicate if found start underscore

  while ((c = fgetc(f)) != EOF) {
    if (c == '_') {
      if (foundStartUnderscore == 0) {
        foundStartUnderscore = 1;
      }
      else {  // already found start underscore -> print "cat" and reset flag
        printf("%s", chooseWord("verb", NULL));
        foundStartUnderscore = 0;
      }
    }
    else if (c == '\n') {
      if (foundStartUnderscore == 1) {
        perror("found newline before closing underscore");
        exit(EXIT_FAILURE);
      }
      else {
        printf("%c", c);
      }
    }
    else if (foundStartUnderscore == 0) {  // not underscore, so print it
      printf("%c", c);
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("incorrect arguments");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  parseFile(f);
}
