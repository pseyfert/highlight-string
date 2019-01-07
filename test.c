#include "high.h"
#include <stdio.h>

int main() {

  char* t1 = "hello";
  char* t2 = "hello";
  char* s1 = NULL;
  char* s2 = NULL;
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "helllo";
  t2 = "hello";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "helto";
  t2 = "hello";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "hel%o";
  t2 = "hel%o";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "hel%o";
  t2 = "hello";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  return 0;
}
