#ifndef SRC_BACK_H_
#define SRC_BACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_matrix.h"

typedef struct polygon_struct {
  int *name_vertexes;
  int sum_vertexes_in_facets;
} polygon_t;

typedef struct universe {
  int sum_vertexes;
  int sum_facets;
  int v;
  double *array_3d;
  int *indexes_array;
  matrix_t matrix_3d;
  polygon_t *polygons;
  double max;
  double min;
} t_universe;

int loading(t_universe *, char *);
matrix_t moving(t_universe *, double, double, double);
matrix_t rotating(t_universe *, double, double, double);
matrix_t scaling(t_universe *, double, double, double);
void matrixToArray(t_universe *);
void arrayofstructureToArray(t_universe *);

#endif  // SRC_BACK_H_
