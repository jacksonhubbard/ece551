#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned base, unsigned exponet) {
  if (exponet == 0) {
    return 1;
  }
  else {
    return (base * power(base, exponet - 1));
  }
}
