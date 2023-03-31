#include <stdio.h>
#include "chart.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

char * replace(
    char const * const original,
    char const * const pattern,
    char const * const replacement
) {
  size_t const replen = strlen(replacement);
  size_t const patlen = strlen(pattern);
  size_t const orilen = strlen(original);

  size_t patcnt = 0;
  const char * oriptr;
  const char * patloc;

  // find how many times the pattern occurs in the original string
  for (oriptr = original; (patloc = strstr(oriptr, pattern)); oriptr = patloc + patlen)
    patcnt++;

  {
    // allocate memory for the new string
    size_t const retlen = orilen + patcnt * (replen - patlen);
    char * const returned = (char *) malloc( sizeof(char) * (retlen + 1) );

    if (returned != NULL) {
      // copy the original string,
      // replacing all the instances of the pattern
      char * retptr = returned;
      for (oriptr = original; (patloc = strstr(oriptr, pattern)); oriptr = patloc + patlen) {
        size_t const skplen = patloc - oriptr;
        // copy the section until the occurence of the pattern
        strncpy(retptr, oriptr, skplen);
        retptr += skplen;
        // copy the replacement
        strncpy(retptr, replacement, replen);
        retptr += replen;
      }
      // copy the rest of the string.
      strcpy(retptr, oriptr);
    }
    return returned;
  }
}

// char *expr; //Указатель на обрабатываемую строку
float eval(char *expr) {
    return pars(expr);
}

int main() {
   /*
    char w;
    scanf("%c", &w);
    if ((w >= 97) && (w <= 122))
        printf("123\n");
    return 0;
   */
    int b = 0;
    char expr[255], expr0[255], *exprx;  // Содержит вычисляемое выражение
    // gets(expr);
    scanf("%s", expr);
    while (expr[b] != '\0') {
        expr0[b] = expr[b];
        b++;
        }
    float x, y, wx = 4*M_PI;
    init_grid();
    for (x = 0; x <= (M_PI * 4); x += (wx/ (WIDTH-1))) {
        b = 0;
        while (expr0[b] != '\0') {
            expr[b] = expr0[b];
            b++;
            }
        expr[b]='\0';
        char buf[255];
        gcvt(x, 10, buf);
        exprx = replace(expr, "x", buf);
        b = 0;
        while (exprx[b] != '\0') {
            expr[b] = exprx[b];
            b++;
            }
        expr[b]='\0';
        free(exprx);
        y = eval(expr);
        plot(rintf(x*WIDTH/wx), rintf(y*HEIGHT/2));
        }
    show_grid();
    return 0;
}
