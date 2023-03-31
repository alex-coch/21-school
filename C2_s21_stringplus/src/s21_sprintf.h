#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "s21_string.h"

typedef struct all_parsing_params {
    char flag[6];
    int width;
    int accur;
    char lenght;
    char specif;
    int width_arg_flag;
    int accur_arg_flag;
    int flag_minus_accur;
    int size_format;
    int spec_pos;
} type_parsing;

typedef struct int_types {
    long *ld;
    int *d;
    short *h;
    unsigned long *lu;
    unsigned *u;
    unsigned short *hu;
} int_type;

typedef struct double_types {
    float *f;
    double *l_f;
    long double *long_f;
} double_type;

int s21_sprintf(char *str, const char *format, ...);
void char_check(type_parsing *spec_type, char *str, int ch, s21_size_t *res_len, int *null_flag);
int itoa(char *str, long int d);
int stoi(char *str, int size);
void output(int counter, int counter_buff, const char *format, char *str);
int check(int counter, const char *str, const char *refer, int ref_point_p);
int all_parsing(const char *format, type_parsing *spec_type);
void all_search(int *counter_buff, int *counter, const char *format, char *refer, char *str,
int ref_point_p);
int ftoa_e(type_parsing *spec_type, long double e, char *str, char specif);
void g_to_str(type_parsing *spec_type, char *str, va_list temp);
void d_to_str(char *out1, type_parsing *spec_type, long int d);
long int stepen(long int b);
int dig_counter(long int d);
void push_zero(char *out, int *stp, int stop);
void itoa_hex(type_parsing *spec_type, long long int d, char *str, int n);
void pnt_to_str(type_parsing *spec_type, long long int int_p, char *str);
void str_to_res_str(type_parsing *spec_type, char *arg_str, char *str);
void hex_oct_dec_convert(char* buffer, int size, type_parsing *spec_type, va_list list_args, int s_s);
void str_to_float(char *buffer, int size, long double *f_arg);
int check_sign(char **str, int* size);
void double_arg_to_str(char* buffer, int size, type_parsing *spec_type, va_list list_args);
int s21_sscanf(const char *str, const char *format, ...);

void yes_null_width(type_parsing *spec_type,  char *str, char *buffer, const char *empty);
void no_null_width(type_parsing *spec_type,  char *str, char *buffer, const char *empty);

void start_sscanf(type_parsing *spec_type, int *used_args, char *buffer, va_list list_args,
int *i, const int *j, const int *k);
void small_parsing(type_parsing *spec_type, const int *ref_point_p, char *str, int *i);

void sscanf_str_to_res(type_parsing *spec_type, char *src, va_list list_args);
void hex_oct_stoi(type_parsing *spec_type, char *buffer, va_list list_args);
void str_to_ch(char *buffer, type_parsing *spec_type, va_list list_arg);
void all_clean(char *str, int size_str);

#endif  // SRC_S21_SPRINTF_H_
