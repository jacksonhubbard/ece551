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

  category_t * one_category = malloc(1 * sizeof(*one_category));
  one_category->name = NULL;
  one_category->n_words = 0;

  catarray_t * all_categories = malloc(1 * sizeof(*all_categories));
  all_categories->n = 0;
  all_categories->arr = one_category;

  all_categories = parseFileForPairs(f, all_categories);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printWords(all_categories);
  freeCatArray(all_categories);

  return EXIT_SUCCESS;
}
