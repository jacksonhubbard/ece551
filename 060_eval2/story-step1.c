#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void parseFile(FILE * f) {
  int c;
  int foundStartUnderscore = 0;

  while ((c = fgetc(f)) != EOF) {
    // if it is a space, go to next char
    //if (c == ' ') {
    //  printf("%c", c);
    //}
    if (c == '_') {
      if (foundStartUnderscore == 0) {  // indicates underscore at start of word
        foundStartUnderscore = 1;
        continue;
      }
      else {  // found end underscore so print cat and reset flag
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
    // if it is non underscore and we are not in middle of word, print it
    else if (foundStartUnderscore == 0) {
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
