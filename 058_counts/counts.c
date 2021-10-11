#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->size = 0;
  counts->countsArr = malloc(1 * sizeof(*counts->countsArr));
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //  printf("%s\n", name);
  int found = 0;
  for (int i = 0; i < c->size; i++) {
    if (name != NULL) {
      if (strcmp(c->countsArr[i]->string, name) == 0) {
        c->countsArr[i]->count++;
        found = 1;
      }
    }
    else {
      if (strcmp(c->countsArr[i]->string, "") == 0) {
        found = 1;
        c->countsArr[i]->count++;
      }
    }
  }
  if (found == 0) {
    if (name != NULL) {
      c->countsArr = realloc(c->countsArr, (c->size + 1) * sizeof(*c->countsArr[0]));

      c->countsArr[c->size] = malloc(sizeof(*(c->countsArr[c->size])));
      c->countsArr[c->size]->string = malloc((strlen(name) + 1) * sizeof(char));
      c->countsArr[c->size]->count = 1;
      strcpy(c->countsArr[c->size]->string, name);
      c->size++;
    }
    else {
      c->countsArr = realloc(c->countsArr, (c->size + 1) * sizeof(*c->countsArr[0]));

      c->countsArr[c->size] = malloc(sizeof(*(c->countsArr[c->size])));
      c->countsArr[c->size]->string = malloc((strlen("") + 1) * sizeof(char));
      c->countsArr[c->size]->count = 1;
      strcpy(c->countsArr[c->size]->string, "");
      c->size++;
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int nullCount = 0;

  for (int i = 0; i < c->size; i++) {
    if (strcmp(c->countsArr[i]->string, "") != 0) {
      fprintf(outFile, "%s: %d\n", c->countsArr[i]->string, c->countsArr[i]->count);
    }
    else {
      nullCount = c->countsArr[i]->count;
    }
  }
  if (nullCount > 0) {
    fprintf(outFile, "<unknown>: %d\n", nullCount);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->countsArr[i]->string);
    free(c->countsArr[i]);
  }
  free(c->countsArr);
  free(c);
}
