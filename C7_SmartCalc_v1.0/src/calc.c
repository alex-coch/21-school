#include "calc.h"

/** @brief Calculates an expression in polish notation.
 *
 *  @param exp a strinf with an expression.
 *  @param x a variable
 *
 *  @return an outcome of evaluation.
 */
double calculate(que* exp, double x) {
  double result = 0.0;
  quEl* curel = exp->tail;
  mstack* stack = stack_init();

  while (curel != NULL) {
    lex* curlex = curel->lexi;
    curel = curel->next;

    // if current lexeme is number
    if (curlex->type == NUMBER) {
      lex* lexnum = (lex*)calloc(1, sizeof(lex));
      lexnum->type = NUMBER;
      if (curlex->chr != 'x') {
        lexnum->num = curlex->num;
      } else {
        lexnum->num = x;
        if (curlex->num < 0) lexnum->num *= -1;
      }
      stack_push(stack, lexnum);
    }
    // if is function
    if (curlex->type == FUNCTION) {
      lex* stackVal = stack_pop(stack);
      if (stackVal->type != NUMBER) printf("\n!ERR:stack->num is NOT a num\n");
      double res_value = calc_fux(stackVal->num, curlex->chr);
      stackVal->num = res_value;
      stack_push(stack, stackVal);
    }
    // if is operator
    if (curlex->type == OPERATOR) {
      lex* num1 = stack_pop(stack);
      lex* num2 = stack_pop(stack);
      if (num1->type != NUMBER) printf("\n!ERR:num1 is NOT a num");
      if (num2->type != NUMBER) printf("\n!ERR:num2 is NOT a num");
      double res_value = calc_nums(num1->num, num2->num, curlex->chr);
      free(num1);
      free(num2);
      lex* lexnum = (lex*)calloc(1, sizeof(lex));
      lexnum->num = res_value;
      lexnum->type = NUMBER;
      stack_push(stack, lexnum);
    }
  }

  lex* stackResult = stack_pop(stack);
  if (stackResult->type != NUMBER) printf("\n!ERR:result is NOT a num\n");
  result = stackResult->num;
  free(stackResult);
  stack_free(stack);
  return result;
}

/** @brief Calculates an arithmentic operation between 2 values.
 *
 *  @param num1 a variable 1.
 *  @param num2 a variable 2.
 *  @param op a token (operation).
 *
 *  @return an outcome of an arithmetic operation.
 */
double calc_nums(double num1, double num2, char op) {
  double retval;
  switch (op) {
    case '+':
      retval = num2 + num1;
      break;
    case '-':
      retval = num2 - num1;
      break;
    case '*':
      retval = num2 * num1;
      break;
    case '/':
      if (fabs(num1) > __FLT_EPSILON__)
        retval = num2 / num1;
      else
        retval = NAN;
      break;
    case '^':
      retval = pow(num2, num1);
      break;
    case MODE:
      retval = fmod(num2, num1);
      break;
    default:
      printf("\n!ERR:UNKNOWN OPERATOR '%c'\n", op);
      break;
  }
  return retval;
}

/** @brief Calculates a function of a value.
 *
 *  @param value a variable.
 *  @param op a token.
 *
 *  @return a function of a value.
 */
double calc_fux(double value, char op) {
  double retval;
  switch (op) {
    case COS:
      retval = cos(value);
      break;
    case SIN:
      retval = sin(value);
      break;
    case TAN:
      retval = tan(value);
      break;
    case ACOS:
      retval = acos(value);
      break;
    case ASIN:
      retval = asin(value);
      break;
    case ATAN:
      retval = atan(value);
      break;
    case SQRT:
      retval = sqrt(value);
      break;
    case LN:
      retval = log(value);
      break;
    case LOG:
      retval = log10(value);
      break;
    default:
      printf("\n!ERR:UNKNOWN FUNCTION '%c'\n", op);
      break;
  }
  return retval;
}

/** @brief Calculates an annuity loan.
 *
 *  @param sum_credit sum of a loan.
 *  @param time_credit a period of loan time.
 *  @param per an interest.
 *  @param month_pay a monthly sum.
 *  @param over_pay an overdraft.
 *  @param all_pay a total sum.
 *
 *  @return a status of operation.
 */
int credit_annuity(double sum_credit, double time_credit, double per,
                   double* month_pay, double* over_pay, double* all_pay) {
  int error = 0;
  double per_m = (per / 12.0) / 100;
  *month_pay = per_m * pow(1 + per_m, time_credit) /
               (pow(1 + per_m, time_credit) - 1) * sum_credit;
  *over_pay = *month_pay * time_credit - sum_credit;
  *all_pay = *over_pay + sum_credit;
  if (isnan(*month_pay) != 0 || isinf(*month_pay) != 0) {
    error = 1;
  }
  return error;
}

/** @brief Calculates an differentiative loan.
 *
 *  @param sum_credit sum of a loan.
 *  @param time_credit a period of loan time.
 *  @param per an interest.
 *  @param month_pay_first a 1st monthly sum.
 *  @param month_pay_last a 1ast monthly sum.
 *  @param over_pay an overdraft.
 *  @param all_pay a total sum.
 *
 *  @return a status of operation.
 */
int credit_dif(double sum_credit, double time_credit, double per,
               double* month_pay_first, double* month_pay_last,
               double* over_pay, double* all_pay) {
  int error = 0;
  per = per / 100;
  *all_pay = 0.0;
  double delta_m = sum_credit / time_credit;
  double buf_sum = sum_credit;
  *month_pay_last = 0.0;
  for (int i = 0; i < time_credit; i++) {
    *month_pay_last = buf_sum * per * 30.4166666666667 / 365 + delta_m;
    buf_sum = buf_sum - delta_m;
    *all_pay = *all_pay + *month_pay_last;
    if (!i) {
      *month_pay_first = *month_pay_last;
    }
  }
  *over_pay = *all_pay - sum_credit;
  if (isnan(*month_pay_first) != 0 || isinf(*month_pay_first) != 0 ||
      isnan(delta_m) != 0 || isinf(delta_m) != 0) {
    error = 1;
  }

  return error;
}

/** @brief Fills out an array of refill payments.
 *
 *  @param re1 an array of month nunbers.
 *  @param re2 an array of payments.
 *  @param count_re an amount of months.
 *  @param count_month a current month.
 *
 *  @return a sum of refill payments.
 */
double get_re_list(double* re1, double const* re2, int count_re,
                   int count_month) {
  double buf = 0.0;
  for (int i = 0; i < count_re; i++) {
    int z = (int)re1[i];
    if (z == count_month) {
      buf += re2[i];
    }
  }
  return buf;
}

/** @brief Fills out an array of withdral payments.
 *
 *  @param wi1 an array of month nunbers.
 *  @param wi2 an array of payments.
 *  @param count_wi an amount of months.
 *  @param count_month a current month.
 *  @param all_sum a total sum.
 *
 *  @return a sum of withdral payments.
 */
double get_wi_list(double* wi1, double const* wi2, int count_wi,
                   int count_month, double all_sum) {
  double buf = 0.0;
  for (int i = 0; i < count_wi; i++) {
    int z = (int)wi1[i];
    if (z == count_month) {
      buf += wi2[i];
    }
  }
  if (buf > all_sum) buf = all_sum;
  return buf;
}

/** @brief Calculates a deposit.
 *
 *  @param re1 an array of month nunbers.
 *  @param re2 an array of payments.
 *  @param count_re an amount of months.
 *  @param wi1 an array of month nunbers.
 *  @param wi2 an array of payments.
 *  @param count_wi an amount of months.
 *  @param all_sum a total sum.
 *  @param tern a period.
 *  @param interest a rate.
 *  @param tax a tax rate.
 *  @param period_s a periodicity term.
 *  @param cap capitalzation.
 *  @param all_interest a total income.
 *  @param all_tax a amount of taxes.
 *  @param all_sum_afer amount of money to widthdraw.
 *
 *  @return a status code.
 */
int deposit_calculator(double* re1, double* re2, int count_re, double* wi1,
                       double* wi2, int count_wi, double all_sum, double tern,
                       double interest, double tax, int period_s, int kap,
                       double* all_interest, double* all_tax,
                       double* all_sum_after) {
  int error = 0;
  *all_interest = 0.0;
  *all_sum_after = 0.0;
  *all_tax = 0.0;
  interest = interest / 100;
  tax = tax / 100;
  if (kap == 0) {
    for (int i = 1; i <= tern; i++) {
      all_sum = all_sum + get_re_list(re1, re2, count_re, i);
      all_sum = all_sum - get_wi_list(wi1, wi2, count_wi, i, all_sum);
      *all_interest += interest / 12 * all_sum;
    }
  } else {
    int p = 0;
    for (int i = 1; i <= tern; i++) {
      all_sum = all_sum + get_re_list(re1, re2, count_re, i);
      all_sum = all_sum - get_wi_list(wi1, wi2, count_wi, i, all_sum);
      if (i % period_s == 0) {
        *all_interest +=
            (interest / 12.0) * period_s * (all_sum + *all_interest);
        p = i;
      } else if (i == tern) {
        int z = i - p;
        *all_interest += (interest / 12.0) * z * (all_sum + *all_interest);
      }
    }
  }
  *all_tax = (*all_interest - 75000) * tax;
  *all_tax = *all_tax < 0 ? 0.0 : *all_tax;
  *all_sum_after = *all_interest + all_sum - *all_tax;
  if (isnan(*all_interest) != 0 || isinf(*all_interest) != 0 ||
      isnan(*all_sum_after) != 0 || isinf(*all_sum_after) != 0 ||
      isnan(*all_tax) != 0 || isinf(*all_tax) != 0) {
    error = 1;
  }
  return error;
}