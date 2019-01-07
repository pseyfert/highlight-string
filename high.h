#include <stdlib.h>    // malloc
#include <string.h>    // strlen
#include <sys/param.h> // MIN

// static const char *on = "%F{red}%B";
// static const char *off = "%b%f";
static const char *on = "\033[1m\033[31m";
static const char *off = "\033[0m";

int percents(char *c) {
  int count = 0;
  for (size_t i = 0; i < strlen(c); ++i) {
    if (c[i] == '%')
      count++;
  }
  return count;
}

char *escape(char *in, size_t p) {
  char *o = (char *)malloc(1 + strlen(in) + p);
  size_t ii = 0;
  for (size_t i = 0; i < strlen(in); ++i) {
    o[ii++] = in[i];
    if (in[i] == '%') {
      o[ii++] = '%';
    }
    // if (ii - i == p)
    //   break;
  }
  o[ii] = '\0';
  return o;
}

// returns the index of the first character that's different
size_t equalbeg(const char *one, const char *two) {
  size_t shorter = MIN(strlen(one), strlen(two));
  for (size_t i = 0; i < shorter; i++) {
    if (one[i] != two[i]) {
      return i;
    }
  }
  return shorter;
}

// returns the quasi-index of the first character that's different
// i.e. 0 if the last char differs
size_t equalend(const char *one, const char *two) {
  size_t o = strlen(one);
  size_t t = strlen(two);
  size_t shorter = MIN(o, t);

  for (size_t i = 0; i < shorter; i++) {
    if (one[o - i - 1] != two[t - i - 1]) {
      return i;
    }
  }
  return shorter;
}

size_t maxtoggle(const char *a, const char *b) {
  size_t relevantlength = MAX(strlen(a), strlen(b));
  // 1 char -> max 1 toggle
  // 2 char -> max 1 toggle
  // 3 char -> max 2 toggle
  // 4 char -> max 2 toggle
  // 5 char -> max 3 toggle
  return (1 + relevantlength) / 2;
}

int high(char *inA, char *inB, char **outA, char **outB) {
  int percentsA = percents(inA);
  int percentsB = percents(inB);

  size_t expected_A_length = (1 + strlen(inA) + percentsA +
                         maxtoggle(inA, inB) * (strlen(on) + strlen(off)));
  size_t expected_B_length = (1 + strlen(inB) + percentsB +
                         maxtoggle(inA, inB) * (strlen(on) + strlen(off)));
  // NB: escaping percent signs don't add toggles, but add characters
  *outA = (char *)malloc(expected_A_length);
  *outB = (char *)malloc(expected_B_length);

  if (percentsA > 0)
    inA = escape(inA, percentsA);
  if (percentsB > 0)
    inB = escape(inB, percentsB);

  size_t goodstart = equalbeg(inA, inB);

  for (size_t i = 0; i < goodstart; ++i) {
    (*outA)[i] = inA[i];
    (*outB)[i] = inB[i];
  }

  size_t iA = goodstart;
  size_t iB = goodstart;
  size_t oA = goodstart;
  size_t oB = goodstart;

  int redA = 0;
  // int redB = 0; // redundant ATM

  for (; iA < strlen(inA) && iB < strlen(inB);) {
    if (inA[iA] == inB[iB]) {
      if (redA) {
        for (size_t tmp = 0; tmp < strlen(off); ++tmp) {
          (*outA)[oA++] = off[tmp];
          (*outB)[oB++] = off[tmp];
        }
        redA = !redA;
      }
      (*outA)[oA++] = inA[iA++];
      (*outB)[oB++] = inB[iB++];
    } else {
      if (!redA) {
        for (size_t tmp = 0; tmp < strlen(on); ++tmp) {
          (*outA)[oA++] = on[tmp];
          (*outB)[oB++] = on[tmp];
        }
        redA = !redA;
      }
      if (inA[iA] != '%')
        (*outA)[oA++] = inA[iA++];
      else {
        (*outA)[oA++] = inA[iA++];
        (*outA)[oA++] = inA[iA++];
      }
      if (inB[iB] != '%')
        (*outB)[oB++] = inB[iB++];
      else {
        (*outB)[oB++] = inB[iB++];
        (*outB)[oB++] = inB[iB++];
      }
    }
  }
  if (iA < strlen(inA)) {
    if (!redA) {
      for (size_t tmp = 0; tmp < strlen(on); ++tmp) {
        (*outA)[oA++] = on[tmp];
      }
    }
    for (; iA < strlen(inA);) {
      (*outA)[oA++] = inA[iA++];
    }
    for (size_t tmp = 0; tmp < strlen(off); ++tmp) {
      (*outA)[oA++] = off[tmp];
    }
  } else {
    if (redA) {
      for (size_t tmp = 0; tmp < strlen(off); ++tmp) {
        (*outA)[oA++] = off[tmp];
      }
    }
  }
  if (iB < strlen(inB)) {
    if (!redA) {
      for (size_t tmp = 0; tmp < strlen(on); ++tmp) {
        (*outB)[oB++] = on[tmp];
      }
    }
    for (; iB < strlen(inB);) {
      (*outB)[oB++] = inB[iB++];
    }
    for (size_t tmp = 0; tmp < strlen(off); ++tmp) {
      (*outB)[oB++] = off[tmp];
    }
  } else {
    if (redA) {
      for (size_t tmp = 0; tmp < strlen(off); ++tmp) {
        (*outB)[oB++] = off[tmp];
      }
    }
  }

  (*outA)[oA] = '\0';
  (*outB)[oB] = '\0';


  if (percentsA > 0)
    free(inA);
  if (percentsB > 0)
    free(inB);
  return 0;
}