#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t size = strlen(inputName);

  char * ans = malloc((size + 8) * sizeof(char));

  for (size_t i = 0; i < size; i++) {
    ans[i] = inputName[i];
  }

  char * test = ".counts";
  int i = 0;
  for (size_t j = size; j < size + 7; j++) {
    ans[j] = test[i];
    i++;
  }

  ans[size + 7] = '\0';

  return ans;
}
