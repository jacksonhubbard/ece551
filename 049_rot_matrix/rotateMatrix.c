#include <stdio.h>
#include <stdlib.h>

void rotate_matrix(FILE * f) {
  int c;
  int lineCount = 0;
  int row = 0;
  char matrix[10][10];

  while ((c = fgetc(f)) != EOF) {
    if (row < 10) {
      if (c != '\n') {
        if (lineCount < 10) {
          matrix[row][lineCount] = c;
        }
        else {
          fprintf(stderr, "%s", "Incorrect length1");
          exit(EXIT_FAILURE);
        }
        lineCount++;
      }
      else {
        row++;
        lineCount = 0;
      }
    }
    else {
      fprintf(stderr, "%s", "Incorrect length2");
      exit(EXIT_FAILURE);
    }
  }

  if (row < 10) {
    fprintf(stderr, "%s", "Incorrect length2");
    exit(EXIT_FAILURE);
  }

  // to print orginal matrix
  //  for (int i = 0; i < 10; i++) {
  // for (int j = 0; j < 10; j++) {
  //  printf("%c", matrix[i][j]);
  // }
  // printf("%s", "\n");
  //}

  for (int k = 0; k < 10; k++) {
    for (int l = 9; l >= 0; l--) {
      printf("%c", matrix[l][k]);
    }
    printf("%s", "\n");
  }
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "%s", "Incorrect arguments");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate_matrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
