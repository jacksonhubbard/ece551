#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

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
  catarray_t * all_categories = setupCategories();

  all_categories = parseFileForPairs(f, all_categories);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printWords(all_categories);
  freeCatArray(all_categories);

  return EXIT_SUCCESS;
}
