#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t size = strlen(inputName);

  char * ans = malloc(size * sizeof(char));

  for (size_t i = 0; i < size; i++) {
    ans[i] = inputName[i];
  }

  char * test = ".counts";
  for (size_t j = size; j < size + 6; j++) {
    ans[j] = test[j - size];
  }

  return ans;
}
