#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

// STACK PART
// lexem type for tokenize
enum lexemeType { NUMBER, OPERATOR, FUNCTION, BRACKET, UNDEFINED };

typedef struct lexemes {
  enum lexemeType type;
  char chr;
  double num;
} lex;

// stack struct with lexem type in it
typedef struct stack_elements stEl;
struct stack_elements {
  lex *lexi;
  stEl *next;
  stEl *prev;
};

typedef struct stacks {
  int size;
  stEl *head;
} mstack;

mstack *stack_init();
lex *stack_pop(mstack *);
void stack_free(mstack *);
void stack_push(mstack *, lex *);
bool stack_add_new_lex(mstack *, lex);

// stack utils
lex lex_init();

// QUEUE PART
typedef struct queue_elements quEl;
struct queue_elements {
  lex *lexi;
  quEl *next;
  quEl *prev;
};

typedef struct queue {
  int size;
  quEl *tail;
} que;

que *queue_init();
lex *queue_pop(que *);
void queue_push(que *, lex *);
void queue_free(que *);
bool queue_add_new_lex(que *, lex);

int credit_annuity(double, double, double, double *, double *, double *);
int credit_dif(double, double, double, double *, double *, double *, double *);

double get_re_list(double *, double const *, int, int);
double get_wi_list(double *, double const *, int, int, double);
int deposit_calculator(double *, double *, int, double *, double *, int, double,
                       double, double, double, int, int, double *, double *,
                       double *);

// DEBUG FUCTIONS - COMMENTS FOR BETTER COVERAGE
// void print_lexem(lex lex);
// void stack_print(mstack *stack);
// void queue_print(que *queue);

#endif  // SRC_STACK_H_
