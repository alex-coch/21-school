#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isalpha isdigit
#include <math.h>

int* getToken(char*);  // Получает лексему из строки
float pars(char*);  // Точка входа анализатора
int fSum(double*);  // Обрабатывает сложение и вычитание
int fMulti(double*);  // Обрабатывает умножение и деление
int fExp(double*);  // Возведение в степень
int fUnary(double*);  // Обработка унарных операторов
int fBrack(double*);  // Обрабатывает выражение в скобках
int fAtom(double*);  // Получает значение числа

char *expr;  // Указатель на обрабатываемую строку
char token[80];  // Лексема
enum {Empty, Operator, Variable, Number} type;  // Тип лексемы
enum {No, Syntax, Zero} error;  // Значение ошибки


#endif  // PARSER_H_INCLUDED
#endif  // SRC_PARSER_H_
