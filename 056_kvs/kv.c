#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * parseLine(char * line) {
  char * key = strtok(line, "=");
  char * value = strtok(NULL, "");
  printf("key: %s\n", key);
  printf("value: %s", value);

  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = key;
  pair->value = value;

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

  kvarray_t * kv_struct = malloc(1 * sizeof(*kv_struct));
  kv_struct->len = 1;
  kv_struct->arr = malloc(kv_struct->len * sizeof(*kv_struct->arr));

  int i = 0;

  while ((read_size = getline(&line, &len, f)) != -1) {
    kvpair_t * currPair = parseLine(line);
    printf("%s\n", currPair->key);

    pairCount++;
    kv_struct->len++;
    kv_struct->arr = realloc(kv_struct->arr, kv_struct->len * sizeof(*kv_struct->arr));

    strcpy(currPair->key, kv_struct->arr[i].key);
    strcpy(currPair->value, kv_struct->arr[i].value);

    printf("pairArr[%d]: %s, %s\n\n", i, kv_struct->arr[i].key, kv_struct->arr[i].value);
    i++;
  }
  printf("%s\n", "Done reading lines, Testing some values");
  printf("Key of pairArr[0] = %s, should be apple\n", kv_struct->arr[0].key);
  printf("Key of pairArr[3] = %s, should be grapes\n\n", kv_struct->arr[3].key);

  fclose(f);
  if (line) {
    free(line);
  }

  kvarray_t * kv_arr = malloc(1 * sizeof(*kv_arr));

  //kv_arr->len = pairCount;
  //kv_arr->arr = pairArr;

  printf("%s\n", "looping over arr assigned to struct");
  for (int j = 0; j < pairCount; j++) {
    printf("key: %s value: %s\n", kv_struct->arr[j].key, kv_struct->arr[j].value);
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
