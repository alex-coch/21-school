#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2, MALLOC_FAILED = 3 };
enum { FAILURE = 0, SUCCESS = 1 };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(const int rows, const int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *const A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void adjoint(matrix_t *A, matrix_t *result);
double det(double **m, int size);
void get_cofactor(double **m, double **tmp, int skip_row, int skip_col,
                  int size);

int is_correct(matrix_t *A);
#endif  // SRC_S21_MATRIX_H_
