#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * countsStruct = createCounts();  // has an countsArr ** arr and size

  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;

  FILE * f = fopen(filename, "r");
  while ((len = getline(&line, &sz, f)) >= 0) {
    char * color1 = strtok(line, "\n");
    char * color = lookupValue(kvPairs, color1);

    //printf("%s\n", color);
    addCount(countsStruct, color);
    free(color);
    free(color1);
  }

  // read line by line and call addCount
  //for (size_t i = 0; i < kvPairs->len; i++) {
  //addCount(countsStruct, kvPairs->arr[i].value);
  // }
  //printCounts(countsStruct, stdout);
  fclose(f);
  free(line);
  free(f);
  return countsStruct;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "Usage: key/values inputFileName(s)\n");
    return EXIT_FAILURE;
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    fclose(f);

    //free the memory for outName and c
    free(outName);
    free(c);
    //    printf("%s", "new inputfile\n");
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
