#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (!is_correct(A)) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    ret = CALC_ERROR;
  } else if (s21_create_matrix(A->columns, A->rows, result) != OK)
    ret = MALLOC_FAILED;
  if (!ret) adjoint(A, result);
  return ret;
}
