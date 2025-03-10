#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (!is_correct(A) || !is_correct(B)) {
    ret = INCORRECT_MATRIX;
  } else if ((A->columns != B->rows) || (A->rows != B->columns)) {
    ret = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    ret = MALLOC_FAILED;
  }
  if (!ret) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}
