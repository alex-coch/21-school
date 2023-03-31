#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int, int, matrix_t *);
void s21_remove_matrix(matrix_t *);
int s21_eq_matrix(matrix_t *, matrix_t *);
int s21_mult_matrix(matrix_t *, matrix_t *, matrix_t *);

#endif  // SRC_S21_MATRIX_H_
