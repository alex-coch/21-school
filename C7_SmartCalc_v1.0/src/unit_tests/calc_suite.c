#include <check.h>
#include <math.h>

#include "../calc.h"
#include "../pars.h"

/** @brief Numbers comparision.
 *
 *  Compares two numbers taking them as arguments and returning an
 *         integer value.
 *
 *  @param num1 a first double argument.
 *  @param num2 a secomd double argument.
 *
 *  @return The test results
 */
bool nums_cmp(double num1, double num2) {
  int ret = false;
  if ((isnan(num1) && isnan(num2)) || (isinf(num1) && isinf(num2))) {
    ret = true;
  }
  // else if (isinf(num1) && isinf(num2))
  //   ret = true;
  else {
    ret = (fabs((num1 - num2)) < __FLT_EPSILON__);
  }
  return ret;
}

/** @brief The test for functions str_to_polish and calculate.
 *
 *  Transfers a string to the polish notation and then calculates outcome.
 *
 *  @param calc_test1 a test case.
 *
 *  @return void
 */
START_TEST(calc_test1) {
  char str[] = "-476567mod693+1/ln(x)+sin(x)+(3-3)*1+3^4^4";
  double x = 18.17;
  double expected =
      -476567 % 693 + 1 / log(x) + sin(x) + (3 - 3) * 1 + pow(3, pow(4, 4));
  que* converted;
  if (str_to_polish(str, &converted)) {
    double result = calculate(converted, x);
    // printf("res = %lf\n", result);
    // printf("exp = %lf\n", expected);
    ck_assert_msg(nums_cmp(result, expected), "exp: %.lf\nres: %.lf", expected,
                  result);
  } else {
    ck_abort_msg("test fail");
  }
  queue_free(converted);
}
END_TEST

/** @brief The test for functions str_to_polish and calculate.
 *
 *  Transfers a string to the polish notation and then calculates outcome.
 *
 *  @param calc_test2 a test case.
 *
 *  @return void
 */
START_TEST(calc_test2) {
  char str[] =
      "asin(x+45)+cos(x)/"
      "tan(x)-acos(x-0.122)*asin(x)-atan(x)-sqrt(4)+ln(x)+log(x)+ ln(123^x)";
  double x = 0.170001;
  double expected = asin(x + 45) + acos(x) / tan(x) -
                    acos(x - 0.122) * asin(x) - atan(x) - sqrt(4) + log(x) +
                    log10(x) + log10(pow(12312, x)) + 1;
  que* converted;
  if (str_to_polish(str, &converted)) {
    double result = calculate(converted, x);
    ck_assert_msg(nums_cmp(result, expected), "exp: %f\nres: %f", expected,
                  result);
  } else {
    ck_abort_msg("parse fail");
  }
  queue_free(converted);
}
END_TEST

/** @brief The test for functions str_to_polish and calculate.
 *
 *  Transfers a string to the polish notation and then calculates outcome.
 *
 *  @param calc_test3 a test case.
 *
 *  @return void
 */
START_TEST(calc_test3) {
  char str[] = "12+log(10)+12";
  double x = 0.00;
  double expected = 25;
  que* converted;
  if (str_to_polish(str, &converted)) {
    double result = calculate(converted, x);
    // printf("res = %.9f\n", result);
    // printf("exp = %.9f\n", expected);
    ck_assert_msg(nums_cmp(result, expected), "exp: %f\nres: %f", expected,
                  result);
  } else {
    ck_abort_msg("parse fail");
  }
  queue_free(converted);
}
END_TEST

/** @brief The test for functions credit_annuity, credit_dif, deposit_calculator
 *
 *  @param calc_test4 a test case.
 *
 *  @return void
 */
START_TEST(calc_test4) {
  double month_pay = 0, over_pay = 0, all_pay = 0, month_pay_first = 0,
         month_pay_last = 0;

  ck_assert_int_eq(credit_annuity(100, 12, 10, &month_pay, &over_pay, &all_pay),
                   0);
  ck_assert_int_eq(credit_dif(0, 12, 12, &month_pay_first, &month_pay_last,
                              &over_pay, &all_pay),
                   0);

  double all_interest = 0, all_tax = 0, all_sum_after = 0;
  double re1[1], re2[1], wi1[1], wi2[1];
  re1[0] = 1;
  re2[0] = 1;
  wi1[0] = 2;
  wi2[0] = 2;

  // printf("%lf\n", get_re_list(re1, re2, 1, 1));

  // UNUSED(wi1);
  // UNUSED(wi2);
  // UNUSED(re1);
  // UNUSED(re2);
  ck_assert_int_eq(
      deposit_calculator(re1, re2, 1, wi1, wi2, 1, 100, 12, 10, 13, 1, 1,
                         &all_interest, &all_tax, &all_sum_after),
      0);
}
END_TEST

/*_______SUITE_______*/
Suite* calc_suite(void) {
  Suite* suite = suite_create("calc suite");
  TCase* cases = tcase_create("calc case");

  tcase_add_test(cases, calc_test1);
  tcase_add_test(cases, calc_test2);
  tcase_add_test(cases, calc_test3);
  tcase_add_test(cases, calc_test4);

  // tcase_set_timeout(cases, 9999999);

  suite_add_tcase(suite, cases);
  return suite;
}
