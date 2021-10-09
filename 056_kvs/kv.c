#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t parseLine(char * line) {
  char * key = strtok(line, "=");
  char * value = strtok(NULL, "");
  printf("key: %s\n", key);
  printf("value: %s", value);

  kvpair_t pair;
  pair.key = key;
  pair.value = value;
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  char * line = NULL;
  size_t len = 0;
  ssize_t read_size;
  int pairCount = 0;

  kvpair_t * pairArr = NULL;

  pairArr = malloc(1 * sizeof(kvpair_t));

  int i = 0;

  while ((read_size = getline(&line, &len, f)) != -1) {
    kvpair_t currPair = parseLine(line);
    pairCount++;
    pairArr = realloc(pairArr, pairCount * sizeof(kvpair_t));
    pairArr[i] = currPair;
    printf("pairArr[%d]: %s, %s\n", i, pairArr[i].key, pairArr[i].value);
    i++;
  }
  printf("%s\n", "Done reading lines, Testing some values");
  printf("Key of pairArr[0] = %s, should be apple\n", pairArr[0].key);
  printf("Key of pairArr[3] = %s, should be grapes\n\n", pairArr[3].key);

  fclose(f);
  if (line) {
    free(line);
  }

  kvarray_t * kv_arr = malloc(1 * sizeof(kvpair_t));

  kv_arr->len = pairCount;
  kv_arr->arr = pairArr;

  printf("%s\n", "looping over arr assigned to struct");
  for (int j = 0; j < pairCount; j++) {
    printf("key: %s value: %s\n", pairArr[j].key, pairArr[j].value);
    printf("key: %s value: %s\n\n", kv_arr->arr[j].key, kv_arr->arr[j].value);
  }
  return kv_arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  int size = pairs->len;

  for (int i = 0; i < size; i++) {
    free(pairs->arr[i].key);
    free(pairs->arr[i].value);
    free(pairs->arr);
  }
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  printf("%s", "in print func\n");

  int size = pairs->len;
  for (int i = 0; i < size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int size = pairs->len;

  for (int i = 0; i < size; i++) {
    if (strcmp(pairs->arr[i].key, key) == 0) {
      return pairs->arr[i].value;
    }
  }

  return NULL;
}
