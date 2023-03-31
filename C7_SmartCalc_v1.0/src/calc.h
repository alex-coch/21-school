#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define MODE 'm'

#define COS 'c'
#define SIN 's'
#define TAN 't'
#define ACOS 'C'
#define ASIN 'S'
#define ATAN 'T'
#define SQRT 'q'
#define LN 'l'
#define LOG 'L'

#define UNUSED(expr) (void)(expr)

double calculate(que*, double);
double calc_nums(double, double, char);
double calc_fux(double, char);

#endif /* SRC_CALC_H_ */
