#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "incorrect arguments");
    return EXIT_FAILURE;
  }
  int file1Index = 1;
  int file2Index = 2;
  if (argc == 4) {
    file1Index = 2;
    file2Index = 3;
  }
  FILE * fCategories = fopen(argv[file1Index], "r");
  if (fCategories == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }
  FILE * fStoryTemplate = fopen(argv[file2Index], "r");
  if (fStoryTemplate == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }
  catarray_t * all_categories = setupCategories();
  all_categories = parseFileForPairs(fCategories, all_categories);
  if (argc == 4) {
    parseFile(fStoryTemplate, all_categories, 1, 1);
  }
  else {
    parseFile(fStoryTemplate, all_categories, 1, 0);
  }
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
