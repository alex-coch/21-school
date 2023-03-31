#include "chart.h"

/* Set "pixel" at specific coordinates */
void plot(int x, int y) {
    if (((HEIGHT/2+y) < HEIGHT) && ((HEIGHT/2+y) > 0)) {
        grid[HEIGHT/2+y][x] = '*';
        }
}

/* Initialize grid */
void init_grid(void) {
    int x, y;
    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            grid[y][x] = '.';
}

/* display grid */
void show_grid(void) {
    int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++)
            putchar(grid[y][x]);
        putchar('\n');
        }
}
