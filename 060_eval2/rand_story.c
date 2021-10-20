#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// step 1
void freePreviousWords(category_t * prevWords) {
  for (size_t i = 0; i < prevWords->n_words; i++) {
    free(prevWords->words[i]);
  }

  free(prevWords->words);
  free(prevWords);
}

void parseFile(FILE * f, catarray_t * categories, int needPrevWords, int removeWords) {
  int c;
  int foundStartUnderscore = 0;  // flag to indicate if found start underscore
  char * currentCategory;
  int sizeOfCategory = 0;
  int i = 0;

  category_t * previousWords = NULL;
  if (needPrevWords == 1) {
    previousWords = malloc(1 * sizeof(*previousWords));
    previousWords->words = malloc(1 * sizeof(*previousWords->words));
    previousWords->words[0] = malloc(1 * sizeof(*previousWords->words[0]));
    previousWords->words[0][0] = '\0';
    previousWords->n_words = 0;
  }

  while ((c = fgetc(f)) != EOF) {
    if (c == '_') {
      if (foundStartUnderscore == 0) {
        foundStartUnderscore = 1;
        currentCategory = NULL;
        sizeOfCategory = 0;
        i = 0;
      }
      else {  // already found start underscore -> print "cat" and reset flag
        currentCategory =
            realloc(currentCategory, (sizeOfCategory + 1) * sizeof(*currentCategory));
        currentCategory[i] = '\0';
        handleReplacement(categories, currentCategory, previousWords, removeWords);
        foundStartUnderscore = 0;
        free(currentCategory);
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
    else {  // middle of an underscore word
      sizeOfCategory++;

      currentCategory =
          realloc(currentCategory, sizeOfCategory * sizeof(*currentCategory));
      currentCategory[i] = c;
      i++;
    }
  }
  if (needPrevWords) {
    freePreviousWords(previousWords);
  }
}

int isNumber(char * category) {
  int int_value = atoi(category);
  if (int_value != 0) {
    return 1;
  }
  return 0;
}

void addWordToPrevWords(category_t * prevWords, const char * currentWord) {
  prevWords->n_words++;
  int currentIndex = prevWords->n_words - 1;
  if (currentIndex == 0) {
    free(prevWords->words[0]);
  }
  prevWords->words =
      realloc(prevWords->words, prevWords->n_words * sizeof(*prevWords->words));
  prevWords->words[currentIndex] =
      malloc((strlen(currentWord) + 1) * sizeof(*(prevWords->words[currentIndex])));
  strcpy(prevWords->words[currentIndex], currentWord);
}

void removeWordFromCategory(const char * currentWord,
                            char * currentCategory,
                            catarray_t * categories) {
  for (size_t i = 0; i < categories->n; i++) {
    if (strcmp(categories->arr[i].name, currentCategory) == 0) {
      for (size_t j = 0; j < categories->arr[i].n_words; j++) {
        if (strcmp(categories->arr[i].words[j], currentWord) == 0) {
          // know that j = position of word to remove

          for (size_t k = j; k < (categories->arr[i].n_words - 1); k++) {
            categories->arr[i].words[k] = realloc(
                categories->arr[i].words[k], strlen(categories->arr[i].words[k + 1]) + 1);
            strcpy(categories->arr[i].words[k], categories->arr[i].words[k + 1]);
          }
          free(categories->arr[i].words[categories->arr[i].n_words - 1]);
          categories->arr[i].words = realloc(
              categories->arr[i].words,
              (categories->arr[i].n_words - 1) * sizeof(*categories->arr[i].words));
          categories->arr[i].n_words--;
        }
      }
    }
  }
}

void handleReplacement(catarray_t * categories,
                       char * currentCategory,
                       category_t * prevWords,
                       int removeWords) {
  if (categories == NULL) {
    printf("%s", chooseWord("verb", NULL));
  }
  else {
    if (isNumber(currentCategory) == 0) {
      const char * chosenWord = chooseWord(currentCategory, categories);
      printf("%s", chosenWord);
      addWordToPrevWords(prevWords, chosenWord);

      if (removeWords) {
        removeWordFromCategory(chosenWord, currentCategory, categories);
      }
    }
    else {  // it is a num
      size_t indexToGoBackTo = atoi(currentCategory);
      size_t numberOfWords = prevWords->n_words;
      size_t indexOfPrevWord = numberOfWords - indexToGoBackTo;
      if (indexToGoBackTo <= prevWords->n_words) {
        char * wordToPrint = prevWords->words[indexOfPrevWord];
        addWordToPrevWords(prevWords, wordToPrint);
        printf("%s", wordToPrint);
      }
      else {
        perror("Index to go back is greater than number of previous words");
        exit(EXIT_FAILURE);
      }
    }
  }
}

// step 2
catarray_t * setupCategories() {
  category_t * one_category = malloc(1 * sizeof(*one_category));
  one_category->name = NULL;
  one_category->n_words = 0;

  catarray_t * all_categories = malloc(1 * sizeof(*all_categories));
  all_categories->n = 0;
  all_categories->arr = one_category;
  return all_categories;
}

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
    if (currCategory->words[i] != NULL) {
      free(currCategory->words[i]);
    }
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
