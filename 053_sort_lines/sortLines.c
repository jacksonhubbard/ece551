#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void inputs(FILE * f) {
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  int numLines = 0;

  int i = 0;
  char ** data = malloc(1 * sizeof(*data));
  while ((len = getline(&line, &sz, f)) >= 0) {
    //    printf("%s", line);
    numLines++;
    data = realloc(data, (numLines * sizeof(*data)));
    data[i] = malloc(strlen(line) + 1);
    strcpy(data[i], line);
    i++;
  }

  // print out each element of data
  //  printf("%d", i);
  //for (int i = 0; i < numLines; i++) {
  //  printf("%s", data[i]);
  // }

  sortData(data, numLines);

  // print out each element of data
  for (int i = 0; i < numLines; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }

  free(line);
  free(data);
}

void noInputs() {
  inputs(stdin);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  if (argc == 1) {
    noInputs();
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      inputs(f);

      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
