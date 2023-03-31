#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    ret = CALC_ERROR;
  } else {
    for (int i = 0; i < A->rows && ret == SUCCESS; i++)
      for (int j = 0; j < A->columns && ret == SUCCESS; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) ret = FAILURE;
  }
  return ret;
}
