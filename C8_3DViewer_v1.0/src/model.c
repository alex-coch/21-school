#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_matrix.h"

/** @brief Transforms a matrix to an array.
 *
 *  @param data a pointer to the t_universe structure.
 *
 *  @return void.
 */
void matrixToArray(t_universe *data) {
  data->min = 0;
  data->max = 0;
  data->array_3d = calloc(sizeof(double), (data->sum_vertexes + 1) * 3);
  int k = 0;
  for (int i = 0; i <= data->sum_vertexes; i++) {
    for (int j = 0; j < 3; j++, k++) {
      data->array_3d[k] = data->matrix_3d.matrix[i][j];

      if (data->array_3d[k] < data->min) {
        data->min = data->array_3d[k] * 2;
      }
      if (data->array_3d[k] > data->max) {
        data->max = data->array_3d[k] * 2;
      }
    }
  }
  if (fabs(data->min) > fabs(data->max)) {
    data->max = fabs(data->min);
  } else {
    data->min = -fabs(data->max);
  }
  s21_remove_matrix(&data->matrix_3d);
}

/** @brief Fills an array with structures.
 *
 *  @param data a pointer to the t_universe structure.
 *
 *  @return void.
 */
void arrayofstructureToArray(t_universe *data) {
  data->indexes_array = calloc(sizeof(int), data->v * 2);
  for (int d = 1, k = 0; d <= data->sum_facets; d++, k++) {
    for (int p = 0; p < data->polygons[d].sum_vertexes_in_facets; p++, k++) {
      data->indexes_array[k] = data->polygons[d].name_vertexes[p];
      if (p != 0) {
        k++;
        data->indexes_array[k] = data->indexes_array[k - 1];
      }
    }
    data->indexes_array[k] = data->polygons[d].name_vertexes[0];
  }
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
}

/** @brief Loads a model from a file.
 *
 *  @param data a pointer to a first matrix.
 *  @param file_name a name of a file with a model.
 *
 *  @return a status code of an operation.
 */
int loading(t_universe *data, char *file_name) {
  FILE *f;
  int ret = 0;

  f = fopen(file_name, "r+");
  if (!f) {
    printf(" %s: No such file or directory", file_name);
    ret = 1;
  } else {  // read sum_vertexes and sum_facets
    data->sum_vertexes = 0;
    data->sum_facets = 0;
    char str[1025] = "";
    while (fgets(str, 1024, f) != NULL) {
      if (str[0] == 'v' && str[1] == ' ') data->sum_vertexes++;
      if (str[0] == 'f' && str[1] == ' ') data->sum_facets++;
    }
    fclose(f);

    s21_create_matrix(data->sum_vertexes + 1, 3, &data->matrix_3d);
    data->polygons = calloc(data->sum_facets + 1, sizeof(polygon_t));
    f = fopen(file_name, "r+");
    if (f) {
      data->v = 0;
      char str[1025] = "";
      for (int t = 0, d = 0;
           fgets(str, 1024, f) != NULL;) {     // d = 0 add for part 2
        if (str[0] == 'v' && str[1] == ' ') {  // loading vertexes
          t++;
          for (int i = 2, p = 0; str[i] != '\0'; i++, p++) {
            if (strchr("-1234567890", str[i])) {
              data->matrix_3d.matrix[t][p] = atof(str + i);
              for (int k = i; strchr("-1234567890.", str[k]); k++, i++) {
                continue;
              }
            }
          }
        }
        if (str[0] == 'f' && str[1] == ' ') {  // loading facets
          d++;
          for (int i = 2; str[i] != '\0'; i++) {
            if (strchr(" ", str[i - 1]) && strchr("1234567890", str[i])) {
              data->polygons[d].sum_vertexes_in_facets++;
              data->v++;
            }
          }
          data->polygons[d].name_vertexes =
              calloc(data->polygons[d].sum_vertexes_in_facets, sizeof(int));
          for (int i = 2, p = 0; str[i] != '\0'; i++) {
            if (strchr(" ", str[i - 1]) && strchr("1234567890", str[i])) {
              data->polygons[d].name_vertexes[p] = atoi(str + i);
              p++;
            }
          }
        }
      }
      fclose(f);
    }
  }

  return ret;
}

/** @brief Moves a matrix to coordinates a, b, c.
 *
 *  @param a coordinate a.
 *  @param b coordinate b.
 *  @param c coordinate c.
 *
 *  @return a resulting matrix.
 */
matrix_t moving(t_universe *data, double a, double b, double c) {
  // x1     1 0 0 a     x
  // y1  =  0 1 0 b  *  y
  // z1     0 0 1 c     z
  // 1      0 0 0 1     1
  matrix_t move;
  s21_create_matrix(4, 4, &move);
  for (int i = 0, j = 0; i < 4; i++, j++) move.matrix[i][j] = 1;
  move.matrix[3][0] = a;
  move.matrix[3][1] = b;
  move.matrix[3][2] = c;
  matrix_t m_3d;
  s21_create_matrix(data->sum_vertexes + 1, 4, &m_3d);
  for (int i = 1; i < data->sum_vertexes + 1; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 3)
        m_3d.matrix[i][j] = 1;
      else
        m_3d.matrix[i][j] = data->matrix_3d.matrix[i][j];
    }
  }
  matrix_t res_move;
  s21_mult_matrix(&m_3d, &move, &res_move);
  s21_remove_matrix(&move);
  s21_remove_matrix(&m_3d);
  matrix_t result_move;
  s21_create_matrix(data->sum_vertexes + 1, 3, &result_move);
  for (int i = 1; i <= data->sum_vertexes; i++)
    for (int j = 0; j < 3; j++)
      result_move.matrix[i][j] = res_move.matrix[i][j];
  s21_remove_matrix(&res_move);
  return result_move;
}

/** @brief Rotates a matrix to coordinates a, b, c.
 *
 *  @param a coordinate a.
 *  @param b coordinate b.
 *  @param c coordinate c.
 *
 *  @return a resulting matrix.
 */
matrix_t rotating(t_universe *data, double a, double b, double c) {
  // x1     cos(a)  sin(a) 0     x        по оси z по часовой
  // y1  =  -sin(a) cos(a) 0  *  y
  // 1      0       0      1     1

  // turn on axis X
  matrix_t axis_X;
  s21_create_matrix(3, 3, &axis_X);
  axis_X.matrix[1][1] = cos(a);
  axis_X.matrix[1][2] = -sin(a);
  axis_X.matrix[2][2] = cos(a);
  axis_X.matrix[2][1] = sin(a);
  axis_X.matrix[0][0] = 1;
  matrix_t res_turn_on_X;
  s21_mult_matrix(&data->matrix_3d, &axis_X, &res_turn_on_X);
  s21_remove_matrix(&axis_X);

  // turn on axis Y
  matrix_t axis_Y;
  s21_create_matrix(3, 3, &axis_Y);
  axis_Y.matrix[0][0] = cos(b);
  axis_Y.matrix[0][2] = sin(b);
  axis_Y.matrix[1][1] = 1;
  axis_Y.matrix[2][0] = -sin(b);
  axis_Y.matrix[2][2] = cos(b);
  matrix_t res_turn_on_Y;
  s21_mult_matrix(&res_turn_on_X, &axis_Y, &res_turn_on_Y);
  s21_remove_matrix(&res_turn_on_X);
  s21_remove_matrix(&axis_Y);

  // turn on axis Z
  matrix_t axis_Z;
  s21_create_matrix(3, 3, &axis_Z);
  axis_Z.matrix[0][0] = cos(c);
  axis_Z.matrix[0][1] = -sin(c);
  axis_Z.matrix[1][1] = cos(c);
  axis_Z.matrix[1][0] = sin(c);
  axis_Z.matrix[2][2] = 1;
  matrix_t res_turn_on_Z;
  s21_mult_matrix(&res_turn_on_Y, &axis_Z, &res_turn_on_Z);
  s21_remove_matrix(&res_turn_on_Y);
  s21_remove_matrix(&axis_Z);
  return res_turn_on_Z;
}

/** @brief Scales a matrix to coordinates a, b, c.
 *
 *  @param a coordinate a.
 *  @param b coordinate b.
 *  @param c coordinate c.
 *
 *  @return a resulting matrix.
 */
matrix_t scaling(t_universe *data, double a, double b, double c) {
  // x1     a 0 0 0     x
  // y1  =  0 b 0 0  *  y
  // z1     0 0 c 0     z
  // 1      0 0 0 1     1
  matrix_t scale;
  s21_create_matrix(4, 4, &scale);
  scale.matrix[0][0] = a;
  scale.matrix[1][1] = b;
  scale.matrix[2][2] = c;
  scale.matrix[3][3] = 1;
  matrix_t m_3d;
  s21_create_matrix(data->sum_vertexes + 1, 4, &m_3d);
  for (int i = 1; i <= data->sum_vertexes; i++)
    for (int j = 0; j < 4; j++)
      if (j == 3)
        m_3d.matrix[i][j] = 1;
      else
        m_3d.matrix[i][j] = data->matrix_3d.matrix[i][j];

  matrix_t res_scale;
  s21_mult_matrix(&m_3d, &scale, &res_scale);
  s21_remove_matrix(&scale);
  s21_remove_matrix(&m_3d);
  matrix_t result_scale;
  s21_create_matrix(data->sum_vertexes + 1, 3, &result_scale);
  for (int i = 1; i <= data->sum_vertexes; i++)
    for (int j = 0; j < 3; j++)
      result_scale.matrix[i][j] = res_scale.matrix[i][j];

  s21_remove_matrix(&res_scale);
  return result_scale;
}
