#ifndef SRC_CHART_H_
#define SRC_CHART_H_
#include <stdio.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 25

char grid[HEIGHT][WIDTH];
void plot(int x, int y);
void init_grid(void);
void show_grid(void);
#endif  // SRC_CHART_H_
