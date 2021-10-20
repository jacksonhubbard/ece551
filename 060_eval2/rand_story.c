#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MALLOC/FREE FUNCTIONS
/*
This is a helper funciton used to malloc space for the previous
words array. It takes in a pointer and returns a pointer to the 
array that is now malloced properly.
 */
category_t * setUpPreviousWords(category_t * previousWords) {
  previousWords = malloc(1 * sizeof(*previousWords));
  previousWords->words = malloc(1 * sizeof(*previousWords->words));
  previousWords->words[0] = malloc(1 * sizeof(*previousWords->words[0]));
  previousWords->words[0][0] = '\0';
  previousWords->n_words = 0;
  return previousWords;
}

/*
This function setups up the categories struct my mallocing space
and returning a pointer to the struct.
 */
catarray_t * setupCategories() {
  category_t * one_category = malloc(1 * sizeof(*one_category));
  one_category->name = NULL;
  one_category->n_words = 0;

  catarray_t * all_categories = malloc(1 * sizeof(*all_categories));
  all_categories->n = 0;
  all_categories->arr = one_category;
  return all_categories;
}

/*
This function takes in a pointer to an array struct storing
the words we have previously used. It frees the memory associated
with the previous words. 
 */
void freePreviousWords(category_t * prevWords) {
  for (size_t i = 0; i < prevWords->n_words; i++) {
    free(prevWords->words[i]);
  }

  free(prevWords->words);
  free(prevWords);
}

/*
This function takes in a pointer to a category and frees the 
memory occupied by it. This is called by freeCatArrray()
 */
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

/*
This function takes in a pointer to the a categories array struct
and frees the memory occupied by it. Calls helper function
freeSingleCategory() to help with this process.
 */
void freeCatArray(catarray_t * all_categories) {
  size_t numCategories = all_categories->n;
  for (size_t i = 0; i < numCategories; i++) {
    category_t * currCategory = &(all_categories->arr[i]);
    freeSingleCategory(currCategory);
  }
  free(all_categories->arr);
  free(all_categories);
}

/*
This function takes in pointers to the previousWords array and a pointer
to the current word. It reallocs the previousWords array to make room
for the new word and copies the word in.  
 */
void addWordToPrevWords(category_t * prevWords, const char * currentWord) {
  prevWords->n_words++;
  int currentIndex = prevWords->n_words - 1;
  if (currentIndex == 0) {  // no words stored yet, so cannot malloc without free
    free(prevWords->words[0]);
  }
  prevWords->words =
      realloc(prevWords->words, prevWords->n_words * sizeof(*prevWords->words));
  prevWords->words[currentIndex] =
      malloc((strlen(currentWord) + 1) * sizeof(*(prevWords->words[currentIndex])));
  strcpy(prevWords->words[currentIndex], currentWord);
}

/*
This function takes in pointers to the currentWord, the current
category, and the whole category array struct. It passes over the
(category, word) pairs to delete the current word from the current
category. To do this, it resizes the array for the currentCategory
and frees the pointer to the now extra word.
 */
void removeWordFromCategory(const char * currentWord,
                            char * currentCategory,
                            catarray_t * categories) {
  for (size_t i = 0; i < categories->n; i++) {
    if (strcmp(categories->arr[i].name, currentCategory) == 0) {
      for (size_t j = 0; j < categories->arr[i].n_words; j++) {
        if (strcmp(categories->arr[i].words[j], currentWord) == 0) {
          // know that j = position of word to remove, so take words behind j and move up
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

// HELPER FUNCTIONS

/*
This is a helper function used to indicate if a given category
is a number. Returns flag indicating this.
 */
int isNumber(char * category) {
  int int_value = atoi(category);
  if (int_value != 0) {
    return 1;
  }
  return 0;
}

/*
This function takes in pointers to the categories struct,
the current category, the previous words we have used, and a flag
indicating if we are allowed to repeat words. It is used to handle 
the logic of how to select the random word. 
 */
void handleReplacement(catarray_t * categories,
                       char * currentCategory,
                       category_t * prevWords,
                       int removeWords) {
  if (categories == NULL) {
    printf("%s", chooseWord("verb", NULL));
  }
  else {
    if (isNumber(currentCategory) == 0) {  // if not a number, select word with chooseWord
      const char * chosenWord = chooseWord(currentCategory, categories);
      printf("%s", chosenWord);
      addWordToPrevWords(prevWords, chosenWord);

      if (removeWords) {  // if removeWords flag is set, delete the word we just used
        removeWordFromCategory(chosenWord, currentCategory, categories);
      }
    }
    else {  // it is a number so grab a previous word
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

/*
This function takes in pointers to the category and the whole category
struct. It then passes over the category struct's array checking to see
if the current category is already in the array and returns a value 
indicating if it is. 
 */
int checkIndexForCategory(char * currentCategory, catarray_t * all_categories) {
  for (size_t i = 0; i < all_categories->n; i++) {
    if (strcmp(all_categories->arr[i].name, currentCategory) == 0) {
      return i;
    }
  }
  return -1;
}

// PARSING FUNCTIONS

/*
This function takes in a file pointer to read from and a catarray_t.
It reads the file line by line and then calls the function parseLine()
to help it process the line into categories.
It returns a pointer to the category struct.
 */
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

/*
This function takes in a pointer to a line (read from a file) and
a pointer to the categories array object. It parses the line to separate 
it into categories and words. It checks to see if the category is already
in the array, and if not, mallocs space for it and then adds the new category
and the new word. If it is already in the array, it adds the current word to the 
list.
 */
catarray_t * parseLine(char * line, catarray_t * all_categories) {
  char * category = strtok(line, ":");
  char * word = strtok(NULL, "\n");

  int indexOfKey = checkIndexForCategory(category, all_categories);
  if (indexOfKey == -1) {
    // add a category to all_categories
    int currentIndex = all_categories->n;
    all_categories->n++;
    all_categories->arr =
        realloc(all_categories->arr, all_categories->n * sizeof(*all_categories->arr));
    all_categories->arr[currentIndex].name = malloc(strlen(category) + 1);
    strcpy(all_categories->arr[currentIndex].name, category);
    all_categories->arr[currentIndex].n_words = 1;
    all_categories->arr[currentIndex].words =
        malloc(1 * sizeof(*all_categories->arr[currentIndex].words));
    all_categories->arr[currentIndex].words[0] = malloc(strlen(word) + 1);
    strcpy(all_categories->arr[currentIndex].words[0], word);
  }
  else {
    int currentIndex = all_categories->arr[indexOfKey].n_words;
    all_categories->arr[indexOfKey].n_words++;
    all_categories->arr[indexOfKey].words =
        realloc(all_categories->arr[indexOfKey].words,
                all_categories->arr[indexOfKey].n_words *
                    sizeof(*all_categories->arr[indexOfKey].words));
    all_categories->arr[indexOfKey].words[currentIndex] = malloc(strlen(word) + 1);
    strcpy(all_categories->arr[indexOfKey].words[currentIndex], word);
  }
  return all_categories;
}

/*
This is the main driving function used by several of the steps. It is used to parse
a file, and print out the correct output. It does so by using the categories stored in 
the pointer to the categories struct, and the flags indicating if previous words can be
used and if we can repeat words. 
 */
void parseFile(FILE * f, catarray_t * categories, int usePrevWords, int removeWords) {
  int c;
  int foundStartUnderscore = 0;  // flag to indicate if found start underscore
  char * currentCategory;
  int sizeOfCategory = 0;
  int i = 0;
  category_t * previousWords = NULL;
  if (usePrevWords == 1) {
    previousWords = setUpPreviousWords(previousWords);
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
        fprintf(stderr, "found newline before closing underscore");
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
  if (usePrevWords) {
    freePreviousWords(previousWords);
  }
}
