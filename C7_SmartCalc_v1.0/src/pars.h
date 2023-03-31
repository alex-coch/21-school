#ifndef SRC_PARS_H_
#define SRC_PARS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define s21_INFINITY 1.0 / 0.0
#define s21_NEG_INFINITY -1.0 / 0.0
#define s21_NAN 0.0 / 0.0
#define FAILD -1

// parser
char parse_funx(char*, int*);
char parse_bracket(char*);
char parse_op(char*, int*);
void parse_num(char*, int*, double*, char*);
bool pars_lexeme(char*, lex*, int*, bool);

// notation
bool str_to_polish(char*, que**);
bool op_prior_cmp(char, char);
int op_prior(char);
void rm_spaces(char*);
bool validate(lex, lex);

// utils

#include "stack.h"
#endif  // SRC_PARS_H_
