#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include "../common/common.h"

typedef struct {
  int b;
  int e;
  int E;
  int v;
  int n;
  int s;
  int t;
  int T;
} Options;

void init_options(Options *);
int get_options(char *, Options *);
int process_b(int, char, int *, char, int);
int process_n(int, int *, char, int);
int process_s(char, char, char);
int process_v(char *);
int process_E(char);
int process_T(char);
void cat(int, char *[]);

#endif  // SRC_CAT_S21_CAT_H_
