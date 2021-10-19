#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    perror("incorrect arguments");
    return EXIT_FAILURE;
  }

  FILE * fCategories = fopen(argv[1], "r");
  if (fCategories == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  FILE * fStoryTemplate = fopen(argv[2], "r");
  if (fStoryTemplate == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
}
