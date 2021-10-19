#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

int checkIndexForCategory(char * currentCategory, catarray_t * all_categories) {
  //printf("%s\n", "printing all_cats in checkIdnex");
  //  printWords(all_categories);

  for (size_t i = 0; i < all_categories->n; i++) {
    //    printf("list of keys %s\n", all_categories->arr[i].name);
    if (strcmp(all_categories->arr[i].name, currentCategory) == 0) {
      return i;
    }
  }
  return -1;
}

catarray_t * parseLine(char * line, catarray_t * all_categories) {
  char * key = strtok(line, ":");
  char * value = strtok(NULL, "\n");
  //  printf("current key: %s\n", key);
  //printf("all keys: ");
  //for (size_t i = 0; i < all_categories->n; i++) {
  //printf("%s ", all_categories->arr[i].name);
  // }
  //printf("\n");
  //printf("%s\n", value);

  int indexOfKey = checkIndexForCategory(key, all_categories);
  //printf("%d\n", indexOfKey);
  if (indexOfKey == -1) {
    // add a category to all_categories
    int currentIndex = all_categories->n;
    all_categories->n++;
    all_categories->arr =
        realloc(all_categories->arr, all_categories->n * sizeof(*all_categories->arr));
    all_categories->arr[currentIndex].name = malloc(strlen(key) + 1);
    strcpy(all_categories->arr[currentIndex].name, key);
    all_categories->arr[currentIndex].n_words = 1;
    all_categories->arr[currentIndex].words =
        malloc(1 * sizeof(*all_categories->arr[currentIndex].words));
    all_categories->arr[currentIndex].words[0] = malloc(strlen(value) + 1);
    strcpy(all_categories->arr[currentIndex].words[0], value);
  }
  else {
    int currentIndex = all_categories->arr[indexOfKey].n_words;
    all_categories->arr[indexOfKey].n_words++;
    all_categories->arr[indexOfKey].words =
        realloc(all_categories->arr[indexOfKey].words,
                all_categories->arr[indexOfKey].n_words *
                    sizeof(*all_categories->arr[indexOfKey].words));
    all_categories->arr[indexOfKey].words[currentIndex] = malloc(strlen(value) + 1);
    strcpy(all_categories->arr[indexOfKey].words[currentIndex], value);
  }

  return all_categories;
}

void freeSingleCategory(category_t * currCategory) {
  size_t numWords = currCategory->n_words;

  for (size_t i = 0; i < numWords; i++) {
    free(currCategory->words[i]);
  }
  free(currCategory->words);
  free(currCategory->name);
  //free(currCategory);
}

void freeCatArray(catarray_t * all_categories) {
  size_t numCategories = all_categories->n;

  for (size_t i = 0; i < numCategories; i++) {
    //    printf("%lu\n", i);
    category_t * currCategory = &(all_categories->arr[i]);
    freeSingleCategory(currCategory);
  }
  free(all_categories->arr);
  free(all_categories);
}

catarray_t * parseFileForPairs(FILE * f, catarray_t * all_categories) {
  char * line = NULL;
  size_t len = 0;
  ssize_t read_size;

  while ((read_size = getline(&line, &len, f)) != -1) {
    //printf("line = %s", line);
    parseLine(line, all_categories);
    //printf("%s\n", "now printing all_categories");
    //printWords(all_categories);
    //printf("\n\n");
  }
  free(line);
  return all_categories;
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

  category_t * one_category = malloc(1 * sizeof(*one_category));
  one_category->name = NULL;
  one_category->words = malloc(sizeof(*one_category->words));
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

  //  free(one_category->name);
  free(one_category->words);
  //  free(one_category);

  freeCatArray(all_categories);

  return EXIT_SUCCESS;
}
