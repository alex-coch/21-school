#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int ret = OK;
  if (!is_correct(A) || !result) {
    ret = INCORRECT_MATRIX;
  } else

      if (A->rows != A->columns) {
    ret = CALC_ERROR;
  } else {
    if (A->rows == 1)
      *result = A->matrix[0][0];
    else
      *result = det(A->matrix, A->rows);
  }
  return ret;
}
