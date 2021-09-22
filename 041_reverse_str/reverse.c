#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  if (str == NULL) {
    return;
  }
  else {
    if (!(str[0] == '\n')) {
      size_t len = strlen(str);
      char * i = str;
      char * j = i + len - 1;

      while (i < j) {
        char temp = *i;
        *i = *j;
        *j = temp;
        i++;
        j--;
      }
    }
  }
}

int main(void) {
  //char str0[] = "";
  //char str1[] = "123";
  //char str2[] = "abcd";
  //char str3[] = "Captain's log, Stardate 42523.7";
  //char str4[] = "Hello, my name is Inigo Montoya.";
  //char str5[] = "You can be my wingman anyday!";
  //char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
  //"no tomorrow!";
  //  char * array[] = {NULL, str1, str2, str3, str4, str5, str6};
  char * array[] = {NULL};
  for (int i = 0; i < 1; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
