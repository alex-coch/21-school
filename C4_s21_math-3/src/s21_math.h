#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define S21_PI 3.14159265358979324
#define S21_EXP 2.718281828459045
#define s21_INF 1.0 / 0.0
#define s21_NAN 0.0 / 0.0
#define S21_EPS 1e-17
#define s21_M_PI_2 1.57079632679489661923
#define s21_PI 3.14159265358979323846264338327950288
#define s21_NEG_INF -1.0 / 0.0
#define s21_LN10        2.30258509299
#define s21_ln10 2.30258509299404590109
#define s21_inf 1.0 / 0.0
#define s21_neg_inf -1.0 / 0.0
#define s21_nan 0.0 / 0.0
#define s21_NPI -3.14159265358979324

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

// дополнительные:

struct special {
  int sign;
  long double mantisa;
  long double pow;
  int e;
};

long double range(double x);
long double log_other(double x);
long double log_0_2(double x);
void translate(double x, struct special *_special);
long double checker(double x);
long double s21_factorial(double x);
long double s21_umn(double x, int i);

#endif  // SRC_S21_MATH_H_
