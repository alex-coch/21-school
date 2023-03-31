#include "s21_matrix.h"

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
  int ret = OK;
  if (rows <= 0 || columns <= 0) {
    ret = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));

    if (!result->matrix) {
      ret = MALLOC_FAILED;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i]) {
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
          ret = MALLOC_FAILED;
        }
      }
    }
  }
  return ret;
}
