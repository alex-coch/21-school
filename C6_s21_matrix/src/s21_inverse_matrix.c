#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 0;

  if (!is_correct(A)) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    ret = CALC_ERROR;
  } else {
    double d = 0;
    int code = s21_determinant(A, &d);

    if (fabs(d) < 1e-6 || code) {
      ret = CALC_ERROR;
    } else {
      matrix_t adj = {0};
      if (s21_calc_complements(A, &adj)) {
        ret = MALLOC_FAILED;
      } else {
        matrix_t transposed = {0};

        if (s21_transpose(&adj, &transposed) ||
            s21_create_matrix(A->rows, A->rows, result)) {
          ret = MALLOC_FAILED;
        } else {
          if (A->rows == 1) {
            result->matrix[0][0] = 1 / A->matrix[0][0];
          } else {
            for (int i = 0; i < A->rows; i++)
              for (int j = 0; j < A->rows; j++)
                result->matrix[i][j] = transposed.matrix[i][j] / d;
          }
          s21_remove_matrix(&transposed);
          s21_remove_matrix(&adj);
        }
      }
    }
  }
  return ret;
}
