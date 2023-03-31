#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define for_x for (int x = 0; x < w; x++)
#define for_y for (int y = 0; y < h; y++)
#define for_xy for_x for_y
#define w 80
#define h 25

void clearScreen(void);
void evolve(unsigned *u2);
void game(int msec, int imp);
void show(unsigned *u2);
int proceed(unsigned const *u2, unsigned const *u0, int count);

int main(int argc, char **argv) {
    int ret = 0, msec = 200, imp = 0;
    if (argc > 1)
        msec = atoi(argv[1]);
    if (argc > 2)
        imp = atoi(argv[2]);
    if (msec > 0) {
        game(msec*1000, imp);
        ret = 0;
    } else {
        ret = 1;
        printf("n/a");
        }
    return ret;
    }

int proceed(unsigned const *u2, unsigned const *u0, int count) {
    int ret = 1, fl;
    unsigned *utemp = (unsigned*) malloc(h * w * sizeof(unsigned));
    for_xy
        utemp[x * h + y] = u0[x * h + y];
    if (count == 1) {
        ret = 1;
    } else {
    for (int i = 0; i < count; i++) {
        fl = 0;
        for_xy
            if (u2[x * h + y] != utemp[x * h + y]) {
                fl = 1;
                }
        if (fl == 0) {
            ret = 0;
        }
        evolve(utemp);
        }
    }
    fl = 0;
    for_xy {
        if (u2[x * h + y] == 1) {
            fl = 1;
            }
        }
    if (fl == 0) {
        ret = 0;
    }
    free(utemp);
    return ret;
}

void clearScreen(void) {
    printf("\33[0d\33[2J");
}

void game(int msec, int imp) {
    unsigned *univ2 = (unsigned*) malloc(h * w * sizeof(unsigned));
    unsigned *u0 = (unsigned*) malloc(h * w * sizeof(unsigned));
    char Mstr[w+1];
    int count = 0;
    if (imp == 0) {
        for_xy
            univ2[x * h + y] = rand() < RAND_MAX / 10 ? 1 : 0;
    } else {
            for_y {
                scanf("%80s", Mstr);
                for_x
                    univ2[x * h + y] = Mstr[x] - '0';
                }
            }
    for_xy
        u0[x * h + y] = univ2[x * h + y];
    clearScreen();
    do {
        show(univ2);
        evolve(univ2);
        usleep(msec);
        count++;
    } while (proceed(univ2, u0, count));
    printf("\nGame over");
    free(univ2);
    free(u0);
}

void evolve(unsigned *u2) {
    unsigned *new2 = (unsigned*) malloc(h * w * sizeof(unsigned));
    for_y for_x {
        int n2 = 0;
        for (int y1 = y - 1; y1 <= y + 1; y1++)
            for (int x1 = x - 1; x1 <= x + 1; x1++) {
                if (u2[((y1 + h) % h)  + h * ((x1 + w) % w)])
                    n2++;
                }
        if (u2[x * h + y]) n2--;
        new2[x * h + y] = (n2 == 3 || (n2 == 2 && u2[x * h + y]));
    }
    for_y for_x u2[x * h + y] = new2[x * h + y];
    free(new2);
}

void show(unsigned *u2) {
    printf("\033[H");
    for_y {
        for_x printf(u2[x * h + y] ? "\033[07m  \033[m" : "  ");
        printf("\033[E");
        }
    printf("Ctrl-c to exit");
    fflush(stdout);
}
