#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "incorrect arguments");
    return EXIT_FAILURE;
  }
  FILE * fCategories = fopen(argv[1], "r");
  if (fCategories == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }
  FILE * fStoryTemplate = fopen(argv[2], "r");
  if (fStoryTemplate == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }
  catarray_t * all_categories = setupCategories();
  all_categories = parseFileForPairs(fCategories, all_categories);
  parseFile(fStoryTemplate, all_categories, 1, 0);

  if (fclose(fCategories) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (fclose(fStoryTemplate) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }
  freeCatArray(all_categories);
  return EXIT_SUCCESS;
}
