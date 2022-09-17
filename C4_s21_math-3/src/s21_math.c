#include "s21_math.h"

int s21_abs(int x) {
  return x < 0 ? x *= -1 : x;
}

long double s21_ceil(double x) {
    long int a = (long int)x;
    if (x >= 0 && (double)a != x)
        a+=1;
    return (long double)a;
}

long double s21_exp(double x) {
  long double out = 0;
  if (x < 0) {
    out = 1/s21_exp((-1)* x);
  } else {
        long double dif = 1;
        long double last;
        int n = 0;
        while (dif > S21_EPS) {
            double buff = 1;
            for (int j = 1; j <= n; j++) {
                buff *= x/j;
            }
            out += buff;
            if (n > 0) {
              dif = s21_fabs(out - last);
            }
            last = out;
            n++;
        }
    }
    return out;
}

long double s21_pow(double base, double exp) {
long double rez;
    rez = s21_exp(exp * log(base));
    return rez;
}

long double s21_sqrt(double x) {
  long double result = x / 2;
  if (x < 0) {
    result = -s21_NAN;
  } else if (x == s21_INF) {
    result = s21_INF;
  } else {
    long double temp = 0;
    while (s21_fabs(result - temp) > S21_EPS) {
      temp = result;
      result = (temp + x / temp) / 2;
    }
  }
  return result;
}

long double s21_fabs(double x) {
    return ( x < 0 ? (long double)(x *= -1) : (long double)x);
}

long double s21_fmod(double a, double b) {
  // long double result = s21_fabs(x);
  // if ((result == s21_INF) || (result == s21_NEG_INF) || (x != x) || (y != y) || y == 0) {
  //   result = s21_NAN;
  // } else if (y == 1 || s21_fabs(x) == s21_fabs(y)) {
  //   result = 0.0;
  // } else {
  //   y = s21_fabs(y);
  //   int i = 1;
  //   while (result > y) {
  //     result = s21_fabs(x) - y * i;
  //     i++;
  //   }
  // result = x < 0 ? -result : result;
  // }
  // return result;
  long double res = a < 0 ? -a : a;
  if ((res == s21_inf) || (res == s21_neg_inf) || (a != a) || (b != b) || (b == 0)) {
    res = s21_nan;
  } else {
    double bi = b < 0 ? -b : b;
    int counter = 1;
    while (res >= bi) {
      res = (a < 0 ? -a : a) - bi * counter;
      counter++;
    }
  res = a < 0 ? -res : res;
  }
  return res;


}

long double s21_asin(double x) {
    long double res = s21_atan(x/(s21_sqrt(1-(x * x))));
    return res;
}

long double s21_acos(double x) {
    long double res = 0.0;
    if (x > 1 || x < -1) {
            res = s21_NAN;
        } else {
            res = s21_M_PI_2 - s21_asin(x);
        }
    return res;
}

long double s21_atan(double x) {
    long double out = 0;
    if (x < 1 && x > -1) {
        out = range(x);
    } else {
        if (x == 1) {
            out = S21_PI/4;
        } else if (x == -1) {
            out = -S21_PI/4;
        } else if (x > 1) {
            out = S21_PI/2 - range(1/x);
        } else if (x < -1) {
            out = -S21_PI/2 - range(1/x);
        }
    }
    return out;
}

long double s21_sin(double x) {
    if (x < -s21_PI || x > s21_PI) {
      x = s21_fmod(x, 2 * s21_PI);
    }
    long double temp = x, result = x;
    double n = 3.0;
    int z = -1;
    while (s21_fabs(temp) > S21_EPS) {
      long double p = 1;
      for (int i = 0; i < n; i++) {
        p*= x;
      }
      temp = z * (p / (s21_factorial(n)));
      n += 2.;
      result += temp;
      z *= -1;
    }
    return result;
}

long double s21_cos(double x) {
    if (x < -s21_PI || x > s21_PI) x = s21_fmod(x, 2 * s21_PI);
    long double temp = x, result = 1;
    double n = 2.;
    int z = -1;
    while (s21_fabs(temp) > S21_EPS) {
    long double p = 1;
    for (int i=0; i < n; i++) {
        p*=x;
    }
    temp = z * (p / (s21_factorial(n)));
    n += 2.;
    result += temp;
    z *= -1;
    }
    return result;
}

long double s21_tan(double x) {
    long double res = s21_sin(x) / s21_cos(x);
    return res;
}

long double s21_floor(double x) {
  long double res;
  if (x == s21_INF || x == -s21_INF|| x != x) {
    res = x;
  } else {
    if (x != (int)x) {
      if (x > 0.0) {
        res = (int)x;
      } else {
        res = (int)x - 1;
      }
    } else {
      res = x;
    }
  }
  return res;
}

long double s21_log(double x) {
  long double res;
  if (x == s21_inf) {
    res = s21_inf;
  } else if ((x == s21_neg_inf) || (x != x)) {
    res = s21_nan;
  } else {
    res = (x > 0 && x < 2) ? log_0_2(x) : log_other(x);
  }
  return res;
}

/* Дополнительные функции */

long double range(double x) {  // дополнительный, используется в atan
    long double rez = x, y = x, i = 1;
    while (s21_fabs(rez) > S21_EPS) {
        rez = -1 * rez * x * x * (2 * i - 1) / (2 * i + 1);
        i += 1;
        y += rez;
    }
    return y;
}

long double s21_factorial(double x) {  // дополнительный, используется в sin, cos
    long double res = 1;
    if (x > 0) {
        for (int i = 1; i <= x; i++) {
            res*=i;
        }
    }
    return res;
}

long double log_0_2(double x) {  // дополнительный, используется в log
  x--;
  long double result = x, temp = x;
  long double i = 2;
  while ((result < 0 ? -result : result) > S21_EPS) {
    result *= -x * (i - 1) / i;
    i += 1;
    temp += result;
  }
  return temp;
}

long double log_other(double x) {  // дополнительный, используется в log
    struct special _special;
    translate(x, &_special);
    x = _special.mantisa * _special.sign / 10;
    long double result;
    result = x < 0 ? -s21_nan : x == 0 ? -s21_inf : log_0_2(x) + (_special.e + 1) * s21_ln10;
    return result;
}

void translate(double x, struct special *_special) {  // дополнительный, используется в log
  long double i = 1;
  int es = 0;
  _special->sign = x < 0 ? -1 : 1;
  x *= _special->sign;
  if (x >= 10) {
    while (x >= 10) {
      x /= 10.;
      i *= 10;
      es++;
    }
  } else if (x < 1 && x > 0) {
    while (x < 1) {
      x *= 10;
      i /= 10;
      es--;
    }
  }
  _special->mantisa = x;
  _special->pow = i;
  _special->e = es;
}
