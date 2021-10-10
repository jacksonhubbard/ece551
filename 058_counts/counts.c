#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->size = 0;
  counts->countsArr = malloc(sizeof(*counts->countsArr));
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    if (strcmp(c->countsArr[i].string, name) == 0) {
      c->countsArr[i].count++;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int nullCount = 0;

  for (int i = 0; i < c->size; i++) {
    if (strcmp(c->countsArr[i].string, "NULL") != 0) {
      fprintf(outFile, "%s: %d", c->countsArr[i].string, c->countsArr[i].count);
    }
    else {
      nullCount = c->countsArr[i].count;
    }
  }
  if (nullCount > 0) {
    fprintf(outFile, "<unknown>: %d", nullCount);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->countsArr[i].string);
  }
  free(c->countsArr);
  free(c);
}
