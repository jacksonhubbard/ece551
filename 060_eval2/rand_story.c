#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// step 1
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

// step 2
int checkIndexForCategory(char * currentCategory, catarray_t * all_categories) {
  for (size_t i = 0; i < all_categories->n; i++) {
    if (strcmp(all_categories->arr[i].name, currentCategory) == 0) {
      return i;
    }
  }
  return -1;
}

catarray_t * parseLine(char * line, catarray_t * all_categories) {
  char * key = strtok(line, ":");
  char * value = strtok(NULL, "\n");

  int indexOfKey = checkIndexForCategory(key, all_categories);
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
}

void freeCatArray(catarray_t * all_categories) {
  size_t numCategories = all_categories->n;

  for (size_t i = 0; i < numCategories; i++) {
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
    parseLine(line, all_categories);
  }
  free(line);
  return all_categories;
}
