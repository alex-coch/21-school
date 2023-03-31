#include "s21_matrix.h"

/** @brief Creates a matix.
 *
 *  @param row amount of rows.
 *  @param colums amount of columns.
 *  @param result a pointer to a resulting matrix.
 *
 *  @return a status code of an operation.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int bug = 0;
  if (rows < 1 || columns < 1) {
    bug = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }
  return bug;
}

/** @brief Removes a matix.
 *
 *  @param A a pointer to a removing matrix.
 *
 *  @return void.
 */
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

/** @brief Compares matixes.
 *
 *  @param A a pointer to a first matrix.
 *  @param B a pointer to a second matrix.
 *
 *  @return a status code of an operation.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A == NULL || A->rows < 1 || A->columns < 1 || B == NULL || B->rows < 1 ||
      B->columns < 1) {
    result = FAILURE;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {  // this is A != B
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

/** @brief Multiplies matixes.
 *
 *  @param A a pointer to a first matrix.
 *  @param B a pointer to a second matrix.
 *  @param result a pointer to a resulting matrix.
 *
 *  @return a status code of an operation.
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int bug = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || B == NULL || B->rows < 1 ||
      B->columns < 1) {
    bug = 1;
  } else if (A->columns != B->rows) {
    bug = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return bug;
}
