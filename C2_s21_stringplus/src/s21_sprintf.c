#include "s21_sprintf.h"

int s21_sscanf(const char *str, const char *format, ...) {
    int used_args = 0;
    type_parsing spec_type[20];
    int num_exp_args = all_parsing(format, spec_type);
    int size_src = s21_strlen(str);
    int j = 0;
    va_list list_args;
    va_start(list_args, format);
    for (int i = 0; i < num_exp_args && j < size_src; i++) {
        if (spec_type[i].specif == 'c') {
            spec_type[i].width = 1;
        }
        char *buffer = (char *)calloc(size_src, sizeof(char));
        int k = 0;
        if (buffer) {
            while (*(str + j) != ' ' && *(str + j) != '\n' && *(str + j) != '\t' && j < size_src) {
                *(buffer + k) = *(str + j);
                k++;
                if (spec_type[i].width != 0 && spec_type[i].width == k) {
                    break;
                }
                j++;
            }
            j++;
            while (*(str + j) == ' ' || *(str + j) == '\n' || *(str + j) == '\t') {
                j++;
            }
            start_sscanf(spec_type, &used_args, buffer, list_args, &i, &j, &k);
            free(buffer);
        }
    }
    va_end(list_args);
    return used_args;
}

void start_sscanf(type_parsing *spec_type, int *used_args, char *buffer, va_list list_args,

int *i, const int *j, const int *k) {
    if (spec_type[*i].width_arg_flag == 0) {
        if (spec_type[*i].width == 0) {
            spec_type[*i].width = s21_strlen(buffer);
        }
        s21_size_t size = (s21_size_t)spec_type[*i].width < s21_strlen(buffer) ?
        (s21_size_t)spec_type[*i].width : s21_strlen(buffer);
        if (spec_type[*i].specif == 'c') {
            str_to_ch(buffer, &(spec_type[*i]), list_args);
            (*used_args)++;
        } else if (spec_type[*i].specif == 's') {
            sscanf_str_to_res(&(spec_type[*i]), buffer, list_args);
            (*used_args)++;
        } else if (s21_strchr("xXodu", spec_type[*i].specif) != s21_NULL) {
            int d;
            if (s21_strchr("Xx", spec_type[*i].specif) != s21_NULL) {
                d = 16;
            } else if (spec_type[*i].specif == 'o') {
                d = 8;
            } else {
                d = 10;
            }
            hex_oct_dec_convert(buffer, size, &(spec_type[*i]), list_args, d);
            (*used_args)++;
        } else if (spec_type[*i].specif == 'i') {
            hex_oct_stoi(&(spec_type[*i]), buffer, list_args);
            (*used_args)++;
        } else if (spec_type[*i].specif == 'n') {
            int *n_arg = va_arg(list_args, int *);
            *n_arg = j - k - 2;
            if (*n_arg < 0)
                *n_arg = 0;
            (*used_args)++;
        } else if (s21_strchr("eEfgG", spec_type[*i].specif) != s21_NULL) {
            double_arg_to_str(buffer, size, &(spec_type[*i]), list_args);
            (*used_args)++;
        } else if (spec_type[*i].specif == 'p') {
            hex_oct_dec_convert(buffer, size, &(spec_type[*i]), list_args, 16);
            (*used_args)++;
        }
    }
}

void sscanf_str_to_res(type_parsing *spec_type, char *src, va_list list_args) {
    if (spec_type->lenght == 'l') {
        wchar_t *warg = va_arg(list_args, wchar_t *);
        for (s21_size_t i = 0; i < s21_strlen(src); i++) {
            warg[i] = (wchar_t)(*(src + i));
        }
    } else {
        char *s_arg = va_arg(list_args, char *);
        int size_str = s21_strlen(s_arg);
        if (size_str > 0) {
            for (int j = 0; j < size_str; j++) {
                *(s_arg + j) = 0;
            }
        }
        s21_strncat(s_arg, src, (spec_type->width < (int)s21_strlen(src) ? spec_type->width :
        (int)s21_strlen(src)));
    }
}

void hex_oct_stoi(type_parsing *spec_type, char *buffer, va_list list_args) {
    int size = spec_type->width < (int)s21_strlen(buffer) ? spec_type->width : (int)s21_strlen(buffer);
    if (*buffer == '0') {
        if (*(buffer + 1) == 'x' || *(buffer + 1) == 'X') {
            hex_oct_dec_convert(buffer + 2, size - 2, spec_type, list_args, 16);
        } else {
            hex_oct_dec_convert(buffer + 1, size - 1, spec_type, list_args, 8);
        }
    } else {
        hex_oct_dec_convert(buffer, size, spec_type, list_args, 10);
    }
}

void hex_oct_dec_convert(char *buffer, int size, type_parsing *spec_type, va_list list_args, int s_s) {
    int_type int_val;
    unsigned long arg = 0;
    int sign = check_sign(&buffer, &size);
    for (int i = 0; i < size; i++) {
        arg *= s_s;
        if (*(buffer + i) >= '0' && *(buffer + i) <= '9') {
            arg += (*(buffer + i) - '0');
        } else if (*(buffer + i) >= 'a' && *(buffer + i) <= 'f') {
            arg += (*(buffer + i) - 'W');
        } else if (*(buffer + i) >= 'A' && *(buffer + i) <= 'F') {
            arg += (*(buffer + i) - '7');
        }
    }
    arg *= sign;
    if (s21_strchr("uxXo", spec_type->specif) != s21_NULL) {
        if (spec_type->lenght == 'l') {
            int_val.lu = va_arg(list_args, unsigned long *);
            *(int_val.lu) = (unsigned long)arg;
        } else if (spec_type->lenght == 'h') {
            int_val.hu = va_arg(list_args, unsigned short *);
            *(int_val.hu) = (unsigned short)arg;
        } else {
            int_val.u = va_arg(list_args, unsigned *);
            *(int_val.u) = (unsigned)arg;
        }
    } else if (s21_strchr("di", spec_type->specif) != s21_NULL) {
        if (spec_type->lenght == 'l') {
            int_val.ld = va_arg(list_args, long *);
            *(int_val.ld) = (long)arg;
        } else if (spec_type->lenght == 'h') {
            int_val.h = va_arg(list_args, short *);
            *(int_val.h) = (short)arg;
        } else {
            int_val.d = va_arg(list_args, int *);
            *(int_val.d) = (int)arg;
        }
    } else if (spec_type->specif == 'p') {
        void *p_arg = va_arg(list_args, void **);
        int_val.ld = p_arg;
        *(int_val.ld) = (long)arg;
    }
}

void str_to_ch(char *buffer, type_parsing *spec_type, va_list list_arg) {
    if (spec_type->lenght == 'l') {
       wchar_t *wch = va_arg(list_arg, wchar_t *);
        *wch = (wchar_t)*buffer;
    } else {
        char *ch = va_arg(list_arg, char *);
        *ch = *buffer;
    }
}

void double_arg_to_str(char *buffer, int size, type_parsing *spec_type, va_list list_args) {
    double_type doub_val;
    long double f_arg = 0;
    int left = 0;
    int sign = *buffer == '-' ? -1 : 1;
    int i = 0;
    if (*buffer == '-' || *buffer == '+') {
        i++;
    }
    for (; i < size && *(buffer + i) != '.'; i++) {
        left *= 10;
        left += (*(buffer + i) - '0');
    }
    f_arg = left;
    int count_num = 0;
    int right = 0;
    if (i < size && *(buffer + i) == '.') {
        for (++i; i < size && *(buffer + i) != 'e' && *(buffer + i) != 'E'; i++) {
            right *= 10;
            right += (*(buffer + i) - '0');
            count_num++;
        }
    }
    f_arg += right / pow(10, count_num);
    if (i < size && (*(buffer + i) == 'e' || *(buffer + i) == 'E')) {
        i++;
        int st_sign = *(buffer + i) == '-' ? -1 : 1;
        int st = 0;
        count_num = 0;
        for (++i; i < size && count_num; i++) {  // for (++i; i < size && count_num < 2; i++) {
            st *= 10;
            st += (*(buffer + i) - '0');
        }
        f_arg *= pow(10, st * st_sign);
    }
    f_arg *= sign;
    if (spec_type->lenght == 'l') {
        doub_val.l_f = va_arg(list_args, double *);
        *(doub_val.l_f) = (double)f_arg;
    } else if (spec_type->lenght == 'L') {
        doub_val.long_f = va_arg(list_args, long double *);
        *(doub_val.long_f) = (long double)f_arg;
    } else {
        doub_val.f = va_arg(list_args, float *);
        *(doub_val.f) = (float)f_arg;
    }
}

int s21_sprintf(char *str, const char *format, ...) {
    type_parsing spec_type[20] = {0};
    char *result = (char *)calloc(5000, sizeof(char));
    all_parsing(format, spec_type);
    va_list temp;
    s21_size_t res_len = 0;
    int null_flag = 0;
    va_start(temp, format);
    int size_format = s21_strlen(format);
    if (result) {
        int i = 0;
        int bools = 0;
        int null_size = 0;
        for (int j = 0; j < size_format; j++) {
            if ((*(format + j) == '%') && (spec_type[i].spec_pos == j)) {
                if (spec_type[i].width_arg_flag == 1) {
                    spec_type[i].width = va_arg(temp, int);
                }
                if (spec_type[i].accur_arg_flag == 1) {
                    spec_type[i].accur = va_arg(temp, int);
                }
                if (spec_type[i].specif == 'c') {
                    char_check(&(spec_type[i]), result, va_arg(temp, int), &res_len, &null_flag);
                    null_size = (null_flag == 1 ? s21_strlen(result) : 0);
                } else if (spec_type[i].specif == 'd' || spec_type[i].specif == 'i' ||
                spec_type[i].specif == 'u') {
                    int d = 0;
                    long int ld = 0;
                    unsigned int ud = 0;
                    int marcker = 0;
                    if (spec_type[i].lenght == 'h') {
                        if (spec_type[i].specif == 'u') {
                            unsigned short int usd = va_arg(temp, unsigned int);
                            ld = (long int)usd; marcker = 1;
                        } else {
                            short int sd = va_arg(temp, int);
                            ld = (long int)sd; marcker = 1;
                        }
                    }
                    if (spec_type[i].lenght == 'l' && marcker == 0) {
                            if (spec_type->specif == 'u') {
                                unsigned long int uld = (long int)va_arg(temp, unsigned long int);
                                ld = (long int)uld; marcker = 1;
                            } else {
                                ld = va_arg(temp, long int); marcker = 1;
                            }
                    } else if (marcker == 0) {
                        if (spec_type->specif == 'u') {
                            ud = (long int)va_arg(temp, unsigned int);
                            ld = (long int)ud;
                        } else {
                            d = (long int)va_arg(temp, int);
                            ld = (long int)d;
                        }
                    }
                    d_to_str(result, &spec_type[i], ld);
                } else if (s21_strchr("feE", spec_type[i].specif) != s21_NULL) {
                    long double d_arg;
                    if (spec_type[i].lenght == 'L') {
                        d_arg = va_arg(temp, long double);
                    } else {
                        d_arg = (long double)va_arg(temp, double);
                    }
                    ftoa_e(&(spec_type[i]), d_arg, result, spec_type[i].specif);
                } else if (spec_type[i].specif == 's') {
                    str_to_res_str(&(spec_type[i]), va_arg(temp, char *), result);
                } else if (spec_type[i].specif == '%') {
                    int width = spec_type->width;
                    char* simv;
                    simv = (s21_strchr(spec_type->flag, '0') ? "0" : " ");
                    if (width > 0) {
                        for (int y = 0; y < width - 1; y++) {
                            s21_strcat(result, simv);
                        }
                    }
                    s21_strcat(result, "%");
                    simv = " ";
                    if (width < 0) {
                        width*=(-1);
                        for (int y = 0; y < width - 1; y++) {
                            s21_strcat(result, simv);
                        }
                    }
                } else if (spec_type[i].specif == 'o') {
                    itoa_hex(&(spec_type[i]), va_arg(temp, long long int), result, 8);
                } else if (spec_type[i].specif == 'x' || spec_type[i].specif == 'X') {
                    itoa_hex(&(spec_type[i]), va_arg(temp, long long int), result, 16);
                } else if (spec_type[i].specif == 'g' || spec_type[i].specif == 'G') {
                    bools = 1;
                    g_to_str(&(spec_type[i]), result, temp);
                } else if (spec_type[i].specif == 'p') {
                    pnt_to_str(&(spec_type[i]), va_arg(temp, long long int), result);
                } else if (spec_type[i].specif == 'n') {
                    int *d = va_arg(temp, int *);
                    *d = (int)s21_strlen(result);
                }
                j += spec_type[i].size_format - 1;
                i++;
            } else {
                *(result + s21_strlen(result)) = *(format + j);
            }
        }
        va_end(temp);
        res_len +=  s21_strlen(result);
        int temp_len = res_len;
        s21_strcpy(str, result);
        free(result);
        if (null_flag) {
            *(str + null_size) = '\0';
        } else if (bools == 1) {
            *(str + res_len-2) = '\0';
        } else {
            *(str + temp_len) = '\0';
        }
    }
    return (int) res_len;
}

void char_check(type_parsing *spec_type, char *str, int ch, s21_size_t *res_len, int *null_flag) {
    char *temp_str = (char *)calloc(50, sizeof(char));
    if (temp_str) {
        if (ch == '\0') {
                *res_len += 1;
                *null_flag = (*null_flag == 0 ? 1 : *null_flag);
        }
        char c = ch;
        if (spec_type->width != 0) {
            char empty = (s21_strchr(spec_type->flag, '0') == s21_NULL) ? ' ' : '0';
            if (s21_strchr(spec_type->flag, '-') != s21_NULL) {
                temp_str[0] = c;
                for (int i = 1; i < spec_type->width; i++)
                    *(temp_str + i) = empty;
            } else {
                for (int i = 0; i < spec_type->width - 1; i++)
                    *(temp_str + i) = empty;
                temp_str[spec_type->width - 1] = c;
            }
        } else {
            temp_str[0] = c;
        }
        s21_strcat(str, temp_str);
        free(temp_str);
    }
}

int itoa(char *str, long int d) {
    long temp = d;
    int i = 0;
    do { temp /= 10; i++;
    } while (temp != 0);
    int size = i;
    i--;
    do { *(str + i) = d % 10 + '0';
        d /= 10;
        i--;
    } while (d != 0);
    return size;
}

int stoi(char *str, int size) {
    int sign = check_sign(&str, &size);
    int d = 0;
    for (int i = 0; i < size; i++) {
        if (*(str + i) >= '0' && *(str + i) <= '9') {
            d *= 10;
            d += (*(str + i) - '0');
        }
    }
    d *= sign;
    return d;
}

void pnt_to_str(type_parsing *spec_type, long long int int_p, char *str) {
    itoa_hex(spec_type, int_p, str, 16);
}

void str_to_res_str(type_parsing *spec_type, char *arg_str, char *str) {
    if (arg_str) {
        int size = spec_type->accur < (int) s21_strlen(arg_str) &&
        spec_type->accur != -1 ? spec_type->accur : (int) s21_strlen(arg_str);
        int width = spec_type-> width;
        int dif_size = spec_type-> width - size;
        if ((dif_size > 0 && s21_strchr(spec_type->flag, '-') == s21_NULL)  && (width == 0)) {
        } else if (dif_size > 0 && s21_strchr(spec_type->flag, '-') == s21_NULL) {
            for (int i = 0; i < dif_size; i++) {
                *(str + s21_strlen(str)) = ' ';
            }
        }
        s21_strncat(str, arg_str, size);
        if (dif_size > 0 && s21_strchr(spec_type->flag, '-') != s21_NULL) {
            for (int i = 0; i < dif_size; i++) {
                *(str + s21_strlen(str)) = ' ';
            }
        }
    } else {
        s21_strcat(str, "(null)");
    }
}

int all_parsing(const char *format, type_parsing *spec_type) {
    char flag[] = "-+ 0#";
    char width[] = "1234567890*-";
    char accur[] = ".1234567890*-";
    char lenght[] = "hlL";
    char specif[] = "cdieEfgGosuxXpn%";
    char *refer_pointer[5] = {flag, width, accur, lenght, specif};
    int counter = 0;
    int counter_buff;
    int ref_point_p = 0;
    int i = 0;
    while (*(format + counter) != 0) {
        if (*(format + counter) == '%' && ref_point_p == 0) {
            spec_type[i].spec_pos = counter++;
            for (ref_point_p = 0; ref_point_p < 5; ref_point_p++) {
                char *str = (char *)calloc(30, sizeof(char));
                if (str) {
                    all_search(&counter_buff, &counter, format, refer_pointer[ref_point_p], str, ref_point_p);
                    small_parsing(spec_type, &ref_point_p, str, &i);
                }
            }
            ref_point_p = 0;
            if (s21_strchr(specif, spec_type[i].specif) == s21_NULL) {
                spec_type[i].specif = '%';
            }
            spec_type[i].size_format = counter - spec_type[i].spec_pos;
            i++;
        } else {
            counter++;
        }
    }
    return i;
}

void small_parsing(type_parsing *spec_type, const int *ref_point_p, char *str, int *i) {
    if (*ref_point_p == 0) {
        s21_strcpy(spec_type[*i].flag, str);
        s21_strcat(spec_type[*i].flag, "\0");
    }
    if (*ref_point_p == 1) {
        if (s21_strchr(str, '*') != s21_NULL) {
            spec_type[*i].width_arg_flag = 1;
        } else {
            spec_type[*i].width_arg_flag = 0;
            int size = s21_strlen(str);
            spec_type[*i].width = stoi(str, size);
        }
    }
    if (*ref_point_p == 2) {
        if (s21_strchr(str, '*') != s21_NULL) {
            spec_type[*i].accur_arg_flag = 1;
        } else {
            spec_type[*i].accur = 0;
            spec_type[*i].accur_arg_flag = 0;
            int size = s21_strlen(str);
            spec_type->flag_minus_accur = (s21_strchr(str, '-') ?  1 : 0);
            spec_type[*i].accur = (size == 0 ? -1 : stoi(str, size));
        }
    }
    if (*ref_point_p == 3) {
        spec_type[*i].lenght = str[0];
    }
    if (*ref_point_p == 4) {
        spec_type[*i].specif = str[0];
    }
    free(str);
}

void all_search(int *counter_buff, int *counter, const char *format, char *refer, char *str,
int ref_point_p) {
    *counter_buff = *counter;
    *counter = check(*counter, format, refer, ref_point_p);
    output(*counter, *counter_buff, format, str);
}

int check(int counter, const char *str, const char *refer, int ref_point_p) {
    int i = 0;
    while (s21_strchr(refer, (int)*(str + counter)) != s21_NULL) {
        ++counter;
        i++;
        if (ref_point_p == 4 && i == 1) {
            break;
        }
    }
    return counter;
}

void output(int counter, int counter_buff, const char *format, char *str) {
    int i = 0;
    while (counter_buff < counter) {
        *(str + i) = *(format + counter_buff);
        ++counter_buff;
        i++;
    }
}

void itoa_hex(type_parsing *spec_type, long long int d, char *str, int n) {
    char lenght = spec_type->lenght;
    int width = spec_type->width;
    char* simv;
    simv = (s21_strchr(spec_type->flag, '0') ? s21_strchr(spec_type->flag, '-') ? " " : "0" : " ");
    switch (lenght) {
        case 'h':
            if (spec_type->specif == 'u') {
                d = (unsigned short int)d;
            } else {
                d = (short int)d;
            }
            break;
        case 'l':
            if (spec_type->specif == 'u') {
                d = (unsigned long int)d;
            } else {
                d = (long int)d;
            }
            break;
        default:
            break;
    }
    char *buffer = (char *)calloc(40, sizeof(char));
    if (buffer) {
        char *temp_str = buffer;
        do {
            if (d%n == 10) {
                *temp_str = spec_type->specif == 'x' || spec_type->specif == 'p' ? 'a' : 'A';
            }
            if (d%n == 11) {
            *temp_str = spec_type->specif == 'x' || spec_type->specif == 'p' ? 'b' : 'B';
            }
            if (d%n == 12) {
                *temp_str = spec_type->specif == 'x' || spec_type->specif == 'p' ? 'c' : 'C';
            }
            if (d%n == 13) {
                *temp_str = spec_type->specif == 'x' || spec_type->specif == 'p' ? 'd' : 'D';
            }
            if (d%n == 14) {
            *temp_str = spec_type->specif == 'x' || spec_type->specif == 'p' ? 'e' : 'E';
            }
            if (d%n == 15) {
                *temp_str = spec_type->specif == 'x' || spec_type->specif == 'p' ? 'f' : 'F';
            } else if (d%n > 15 || d%n < 10) {
                *temp_str = (d % n) + '0';
            }
            temp_str++;
            d /= n;
        } while (d != 0);
        char empty = ' ';
        s21_size_t size = s21_strlen(buffer) > (s21_size_t)spec_type->accur ? s21_strlen(buffer) :
        (s21_size_t)spec_type->accur;
        if (s21_strchr(spec_type->flag, '#') != s21_NULL) {
            switch (spec_type->specif) {
                case 'o': {
                    s21_strcat(str, "0");
                    break;
                }
                case 'x': {
                    s21_strcat(str, "0x0");
                    break;
                }
                case 'X': {
                    s21_strcat(str, "0X0");
                    break;
                }
                default:
                    break;
            }
        }

        if (spec_type->specif == 'p') {
            s21_strcat(str, "0x");
        }
        int size_len = s21_strlen(str);
        int size_buf = s21_strlen(buffer);

        if (width > 0 && (s21_strchr(spec_type->flag, '0')) && (!s21_strchr(spec_type->flag, '-'))) {
            char *temp = (char *)calloc(1000, sizeof(char));
            if (temp) {
                for (int i = 0; i < width - size_len - size_buf; i++) {
                    s21_strcat(temp, simv);
                }
                s21_strcat(str, temp);
                free(temp);
            }
        }

        if ((s21_size_t)spec_type->width > size && s21_strchr(spec_type->flag, '-') == s21_NULL) {
            for (s21_size_t i = 0; i < spec_type->width - size; i++) {
                *(str + s21_strlen(str)) = empty;
            }
        }
        if (temp_str - buffer < spec_type->accur) {
            int accur_dif = spec_type->accur - (temp_str - buffer);
            for (int i = 0; i < accur_dif; i++) {
                *(str + s21_strlen(str)) = '0';
            }
        }
        while (temp_str != buffer) {
            *(str + s21_strlen(str)) = *(--temp_str);
        }
        if ((s21_size_t)spec_type->width > size && s21_strchr(spec_type->flag, '-') != s21_NULL) {
            for (s21_size_t i = 0; i < spec_type->width - size; i++) {
                *(str + s21_strlen(str)) = empty;
            }
        }
        size_len = s21_strlen(str);
        if (width > 0 && (!s21_strchr(spec_type->flag, '-'))) {
            char *temp = (char *)calloc(1000, sizeof(char));
            if (temp) {
                for (int i = 0; i < width - size_len; i++) {
                    s21_strcat(temp, simv);
                }
                s21_strcat(temp, str);
                s21_strcpy(str, "");
                s21_strcat(str, temp);
                free(temp);
            }
        } else if (s21_strchr(spec_type->flag, '-') || width < 0) {
            width = (width < 0 ? width * (-1) : width);
            for (int i = 0; i < width - size_len; i++) {
                s21_strcat(str, simv);
            }
        }

        free(buffer);
    }
}

void g_to_str(type_parsing *spec_type, char *str, va_list temp) {
    char specif;
    long double arg_lf;
    if (spec_type->lenght == 'L') {
        arg_lf = va_arg(temp, long double);
    } else {
        arg_lf = (long double)va_arg(temp, double);
    }
    char buff1[200] = "";
    int st = ftoa_e(spec_type, arg_lf, buff1, spec_type->specif == 'g' ? 'e' : 'E');
    if (spec_type->accur == -1) {
        spec_type->accur = 6;
    } else if (spec_type->accur == 0) {
        spec_type->accur = 1;
    }
    if (spec_type->accur > st && st >= -4) {
        spec_type->accur -= (st + 1);
        specif = 'f';
    } else {
        spec_type->accur -= 1;
        specif = spec_type->specif == 'g' ? 'e' : 'E';
    }
    char buff2[200] = "";
    ftoa_e(spec_type, arg_lf, buff2, specif);
    s21_strcat(str, buff2);
}

int ftoa_e(type_parsing *spec_type, long double e, char *str, char specif) {
    char *buffer = (char *)calloc(1000, sizeof(char));
    int size_res = 0;
    int temp_nan_inf = 0;
    if (isnan(e)) {
        temp_nan_inf = 1;
    }
    if (INFINITY == e) {
        temp_nan_inf = 2;
    }
    if (buffer) {
        char *temp_str = buffer;
        int count_l_d = 0;
        if (s21_strchr(spec_type->flag, '+') != s21_NULL && e >= 0) {
            *temp_str = '+';
            temp_str++;
        }
        if (e < -0.0000001) {
            *temp_str = '-';
            temp_str++;
            e = -e;
        }
        if (s21_strchr(spec_type->flag, ' ') != s21_NULL &&
            s21_strchr(buffer, '+') == s21_NULL && s21_strchr(buffer, '-') == s21_NULL) {
            *temp_str = ' ';
            temp_str++;
        }
        int size;
        int accur;
        if (spec_type->specif != 'g' && spec_type->specif != 'G') {
            accur = (spec_type->accur == -1) ? 6 : spec_type->accur;
        } else {
            accur = spec_type->accur;
        }
        if (spec_type->flag_minus_accur == 1) {
            spec_type->width = accur;
            accur = 0;
            s21_strcat(spec_type->flag, "-");
        }

        if ((!isnan(e)) && (INFINITY != e)) {
            if (spec_type->specif == 'e' || spec_type->specif == 'E') {
            } else if (accur == 0) {
                e += 0.5;
            }
            accur = (accur < 0 ? 6 : accur);
            if (specif == 'e' || specif == 'E') {
                while (fabsl(e) >= 10 || fabsl(e) < 1) {
                    if (fabsl(e) > 0 && fabsl(e) < 1) {
                        e *= 10;
                        count_l_d--;
                    } else if (fabsl(e) >= 10) {
                        e /= 9.9999999999;
                        count_l_d++;
                    } else {
                        break;
                    }
                }
                *temp_str = ((char)e) + '0';
            } else if (specif == 'f') {
                size = itoa(temp_str, (long int)e);
                temp_str += size - 1;
            }
            if (accur != 0 || s21_strchr(spec_type->flag, '#') != s21_NULL) {
                *(++temp_str) = '.';
            }
            e -= (int)e;
            spec_type->accur > 0? spec_type->width !=0 ? e = e + (1/ (pow(10, (spec_type->accur +1)))) :
            e + 0.1 : e + 0.00000000001;
            e = e + (pow(10, - (accur+1)) * 5);
            for (int i = 0; i < accur; i++) {
                e *= 10;
                long double temp;
                e = modfl(e, &temp);

                *(++temp_str) = ((int)temp) + '0';
            }
            if (spec_type->specif == 'g' || spec_type->specif == 'G') {
                while (*temp_str == '0') {
                    *temp_str = 2;
                    temp_str--;
                }
                temp_str--;
            }
            int temp_count = count_l_d;
            if (s21_strchr("eE", specif) != s21_NULL) {
                *(++temp_str) = (specif == 'e') ? 'e' : 'E';
                *(++temp_str) = temp_count < 0 ? '-' : '+';
                if (abs(temp_count) < 10) {
                    *(++temp_str) = '0';
                    *(++temp_str) = abs(temp_count) + '0';
                } else {
                    *(++temp_str) = abs(temp_count) / 10 + '0';
                    temp_count %= 10;
                    *(++temp_str) = abs(temp_count) + '0';
                }
            }
        }
        char empty = ' ';
        if (s21_strchr(spec_type->flag, '0') != s21_NULL) {
            empty = '0';
        }
        if ((!isnan(e)) && (INFINITY != e)) {
            yes_null_width(spec_type, str, buffer, &empty);
            s21_strcat(str, buffer);
            no_null_width(spec_type, str, buffer, &empty);
        } else {
            int w = spec_type->width;
            size = 3;
            for (int i = 0; i < (w - size); i++) {
                s21_strcat(str, " ");
            }
            temp_nan_inf == 1 ? s21_strcat(str, "nan") : s21_strcat(str, "inf");
        }
        if (specif == 'e' || specif == 'E') {
            size_res = count_l_d;
        } else {
            size_res = -1;
        }
        free(buffer);
    }
    return size_res;
}

void yes_null_width(type_parsing *spec_type,  char *str, char *buffer, const char *empty) {
    if ((s21_size_t)spec_type->width > s21_strlen(buffer) && s21_strchr(spec_type->flag, '-') == s21_NULL) {
        s21_size_t size = s21_strlen(buffer);
        for (s21_size_t i = 0; i < spec_type->width - size; i++) {
            *(str + s21_strlen(str)) = *empty;
        }
    }
}

void no_null_width(type_parsing *spec_type,  char *str, char *buffer, const char *empty) {
    if ((s21_size_t)spec_type->width > s21_strlen(buffer) && s21_strchr(spec_type->flag, '-') != s21_NULL) {
        s21_size_t size = s21_strlen(buffer);
        for (s21_size_t i = 0; i < spec_type->width - size; i++) {
            *(str + s21_strlen(str)) = *empty;
        }
    }
}

void d_to_str(char *out1, type_parsing *spec_type, long int d) {
    char *flags = spec_type->flag;
    char out[201];
    out[200] = '\0';
    for (int i_tmp = 0; i_tmp < 200; i_tmp++) {
        out[i_tmp] = ' ';
    }
    int w = spec_type->width;
    int accur = spec_type->accur;
    int probel = 0;
    accur = accur == -1 ? 0 : accur;
    int accurf = accur;
    if (s21_strchr(flags, '0') != s21_NULL && (spec_type->accur == -1)) {
        if (d < (long int)0) {
            accur = w-1;
        } else {
            accur = w;
        }
    }
    int stp = 0;
    char sym = (s21_strchr(flags, '+') != s21_NULL && spec_type->specif != 'u') ? '+' : '\0';
    accurf+=((s21_strchr(flags, '+') != s21_NULL) || (d < 0));
    int dig_count = dig_counter(d);
    if (w < 0) {
        *flags = '-';
        w *= (-1);
    }
    if (flags[0] == '-') {
        if (flags[1] == '+')
            flags[1] = '\0';
    }
    w = (w < accur) ? accur : w;
    if (s21_strchr(flags, '0') && (!s21_strchr(flags, '-'))) {
        int i_tmp;
        if (spec_type->accur == -1) {
            i_tmp = 0;
            w = 0;
        } else {
            i_tmp = (w - accur);
        }
        for (; i_tmp < w; i_tmp++) {
            out[i_tmp] = '0';
        }
    }

    if (d < (long int)0) {
        sym = '-';
        d = d * (-1);
    } else {
        if (s21_strchr(flags, '+') || s21_strchr(flags, ' ')) {
            dig_count++;
        }
    }
    w = (w < dig_count) ? dig_count : w;
    int tmp_accur = spec_type->accur;
    if (w > dig_count || accur > dig_count) {
        if ((accur < dig_count  && s21_strchr(flags, '-'))) {
            stp = w - dig_count;
        } else if (tmp_accur && tmp_accur > dig_count) {
            stp = w - accurf;
        } else {
            stp = w - dig_count;
        }
        stp = (stp < 0 ? 0 : stp);
    }
    if (s21_strchr(flags, '-')) {
        probel = stp;
        stp = 0;
    }
    if (s21_strchr(flags, ' ') != 0 && sym == '\0') {
        out[stp] = ' ';
        stp++;
    } else {
        if (sym != '\0') {
            out[stp] = sym;
            stp++;
        }
    }
    dig_count = dig_counter(d);
    long int del = stepen(dig_counter(d));
    long int d_tmp = d;
    if (!s21_strchr(flags, '-') || (!s21_strchr(flags, '0') )) {
        if (s21_strchr(flags, '+')) {
            push_zero(out, &stp, stp  + (accur-1) - dig_count);
        } else {
            push_zero(out, &stp, stp  + (accur) - dig_count);
        }
    }

    for (int i = 0; i < dig_count; i++, stp++) {
        out[stp] = ((long int)d_tmp / del) + 48;
        d_tmp = d_tmp - del * ((long int)d_tmp / del);
        del = del / 10;
    }
    if (s21_strchr(flags, '-')) {
        for (int i = 0; i < probel; i++) {
        out[stp++] = ' ';
        }
    }
    out[stp] = '\0';
    s21_strcat(out1, out);
}

long int stepen(long int b) {
    long int result = 1;
    for (long int i = 1; i < b; i++) {
        result = result * 10;
    }
    return result;
}

int dig_counter(long int d) {
    int i = 1;
    long int temp = 10;
    if (d < 0) {
        (d = d * -1);
        i++;
    }
    while (1) {
        if (d >= temp) {
            temp = temp * 10;
            i++;
        } else {
            break;
        }
    }
    return (i);
}

void push_zero(char *out, int *stp, int stop) {
    for (; *stp < stop; *stp = *stp + 1) {
        out[*stp] = '0';
    }
}

int check_sign(char **str, int *size) {
    int sign = 1;
    if (**str == '-') {
        *str += 1;
        *size -= 1;
        sign = -1;
    }
    return sign;
}
