#include "utils_suite.h"

#include <check.h>

#include "../calc.h"
#include "../pars.h"

/** @brief The test for the functions stack_init, lex_init, stack_add_new_lex.
 *
 *  Adds some elements to a stack.
 *
 *  @param mstacktest01 a test case.
 *
 *  @return void
 */
START_TEST(mstackest01) {
  // test stack 01
  mstack *sta = stack_init();
  lex lex1 = lex_init();
  lex1.type = NUMBER;

  int i = 0;
  for (i = 1; i < 6; i++) {
    lex1.num = (double)i;
    stack_add_new_lex(sta, lex1);
  }

  // printf("\n STACK SIZE %d \n", sta->size);
  // stack_print(sta);
  stack_free(sta);
  ck_assert_int_eq(i, 6);
}
END_TEST

/** @brief The test for the functions queue_init, lex_init, queue_add_new_lex.
 *
 *  Adds some elements to a queue.
 *
 *  @param queue_test01 a test case.
 *
 *  @return void
 */
START_TEST(queue_test01) {
  que *qu = queue_init();
  lex lex1 = lex_init();
  lex1.type = NUMBER;

  int i = 0;
  for (i = 1; i < 6; i++) {
    lex1.num = (double)i;
    queue_add_new_lex(qu, lex1);
  }

  // printf("\n STACK SIZE %d \n", qu->size);
  // queue_print(qu);
  queue_free(qu);
  ck_assert_int_eq(i, 6);
}
END_TEST

/** @brief The test for the function op_prior_cmp.
 *
 *  Compares priorities between some operands.
 *
 *  @param prior_test01 a test case.
 *
 *  @return void
 */
START_TEST(prior_test01) {
  char op1 = '+';
  char op2 = '-';
  ck_assert_int_eq(op_prior_cmp(op1, op2), true);

  op1 = '*';
  op2 = '/';
  ck_assert_int_eq(op_prior_cmp(op1, op2), true);

  op1 = '*';
  op2 = 's';
  ck_assert_int_eq(op_prior_cmp(op1, op2), true);

  op1 = 'm';
  op2 = 'T';
  ck_assert_int_eq(op_prior_cmp(op1, op2), true);

  op1 = '^';
  op2 = '^';
  ck_assert_int_eq(op_prior_cmp(op1, op2), false);
}
END_TEST

/** @brief The test for the function validate.
 *
 *  Compares types of lexems between with each other.
 *
 *  @param valid_test01 a test case.
 *
 *  @return void
 */
START_TEST(valid_test01) {
  lex prevl;
  prevl.type = NUMBER;
  lex curl;
  curl.type = OPERATOR;
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = NUMBER;
  curl.type = 7;
  curl.chr = ')';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = OPERATOR;
  curl.type = NUMBER;
  curl.chr = ')';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = OPERATOR;
  curl.type = 6;
  curl.chr = '(';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = OPERATOR;
  curl.type = FUNCTION;
  curl.chr = ')';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = FUNCTION;
  curl.chr = '(';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = BRACKET;
  prevl.chr = '(';
  curl.type = FUNCTION;
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = BRACKET;
  prevl.chr = '(';
  curl.type = NUMBER;
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = BRACKET;
  prevl.chr = '(';
  curl.type = OPERATOR;
  ck_assert_int_eq(validate(curl, prevl), false);
  //
  prevl.type = BRACKET;
  prevl.chr = ')';
  curl.type = OPERATOR;
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = BRACKET;
  prevl.chr = ')';
  curl.chr = ')';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = BRACKET;
  prevl.chr = ')';
  curl.type = NUMBER;
  curl.chr = '*';
  ck_assert_int_eq(validate(curl, prevl), false);

  prevl.type = UNDEFINED;
  curl.type = FUNCTION;
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = UNDEFINED;
  curl.type = NUMBER;
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = UNDEFINED;
  curl.type = UNDEFINED;
  curl.chr = '(';
  ck_assert_int_eq(validate(curl, prevl), true);

  prevl.type = UNDEFINED;
  curl.type = UNDEFINED;
  curl.chr = '+';
  ck_assert_int_eq(validate(curl, prevl), false);
}
END_TEST

/** @brief The test for the function rm_spaces.
 *
 *  Removes spaces in a string.
 *
 *  @param rm_sp_test01 a test case.
 *
 *  @return void
 */
START_TEST(rm_sp_test01) {
  char op1[] = "de1ete 8*%%space s ";
  char op2[] = "de1ete8*%%spaces";
  // printf("%s \n", op1);
  rm_spaces(op1);
  // printf("%s \n", op1);
  ck_assert_int_eq(strcmp(op1, op2), 0);
}
END_TEST

/** @brief The test for the function parse_funx.
 *
 *  Parses a string to some functions.
 *
 *  @param parse_funx_test01 a test case.
 *
 *  @return void
 */
START_TEST(pars_funx_test01) {
  char *str = "cosi";
  int len = 0;
  // printf("cosi = %c \n", pars_funx(str, &len));
  parse_funx(str, &len);
  ck_assert_int_eq(len, 3);

  char *str1 = "sosi";
  len = 0;
  // printf("sosi = %c \n", pars_funx(str1, &len));
  parse_funx(str1, &len);
  ck_assert_int_eq(len, 0);

  char *str2 = "sin";
  // printf("sin = %c \n", parse_funx(str2, &len));
  parse_funx(str2, &len);
  ck_assert_int_eq(len, 3);

  char *str3 = "asin";
  // printf("asin = %c \n", parse_funx(str3, &len));
  parse_funx(str3, &len);
  ck_assert_int_eq(len, 4);

  char *str4 = "acos";
  // printf("acos = %c \n", parse_funx(str4, &len));
  parse_funx(str4, &len);
  ck_assert_int_eq(len, 4);

  char *str5 = "atan";
  // printf("atan = %c \n", parse_funx(str5, &len));
  parse_funx(str5, &len);
  ck_assert_int_eq(len, 4);

  char *str6 = "sqrt";
  // printf("sqrt = %c \n", parse_funx(str6, &len));
  parse_funx(str6, &len);
  ck_assert_int_eq(len, 4);

  char *str8 = "log";
  // printf("log = %c \n", parse_funx(str8, &len));
  parse_funx(str8, &len);
  ck_assert_int_eq(len, 3);

  char *str7 = "ln";
  // printf("ln = %c \n", parse_funx(str7, &len));
  parse_funx(str7, &len);
  ck_assert_int_eq(len, 2);
}
END_TEST

/** @brief The test for the function parse_num.
 *
 *  Parses a string to some nunbers.
 *
 *  @param parse_num_test01 a test case.
 *
 *  @return void
 */
START_TEST(pars_num_test01) {
  char *str = "-333.4";
  int len;
  double ret_num;
  char ret_chr;
  parse_num(str, &len, &ret_num, &ret_chr);
  // printf("len %.3lf = %d\n", ret_num, len);
  ck_assert_int_eq(len, 6);

  char *str1 = "23 x 333.4";
  parse_num(str1, &len, &ret_num, &ret_chr);
  // printf("len %.3lf = %d\n", ret_num, len);
  ck_assert_int_eq(len, 3);

  char *str2 = "x ";
  parse_num(str2, &len, &ret_num, &ret_chr);
  // printf("len %.3lf %c = %d \n", ret_num, ret_chr, len);
  ck_assert_int_eq(len, 1);

  // parse operators
  len = 0;
  char *str3 = "+-";
  // char op =
  parse_op(str3, &len);
  // printf("lenop %c = %d \n", op, len);
  ck_assert_int_eq(len, 1);

  len = 0;
  char *str4 = "mode";
  // op =
  parse_op(str4, &len);
  // printf("lenop %c = %d \n", op, len);
  ck_assert_int_eq(len, 3);
}
END_TEST

/** @brief The test for the function parse_lexeme.
 *
 *  Parses a string to some lexems.
 *
 *  @param parse_lexeme_test01 a test case.
 *
 *  @return void
 */
START_TEST(pars_lexeme_test01) {
  char *str = "tan-cos(2)";
  int retlen;
  int unary = true;
  lex lexret = lex_init();

  pars_lexeme(str, &lexret, &retlen, unary);
  // printf("len: %c = %d: ", lexret.chr, retlen);
  // print_lexem(lexret);

  char *str2 = "+34.567";
  pars_lexeme(str2, &lexret, &retlen, unary);
  // printf("len: %c = %d: ", lexret.chr, retlen);
  // print_lexem(lexret);

  char *str3 = "(1+1)";
  pars_lexeme(str3, &lexret, &retlen, unary);
  // printf("len: %c = %d: ", lexret.chr, retlen);
  // print_lexem(lexret);

  char *str4 = ")";
  pars_lexeme(str4, &lexret, &retlen, unary);
  // printf("len: %c = %d: ", lexret.chr, retlen);
  // print_lexem(lexret);

  char *str5 = "acos";
  pars_lexeme(str5, &lexret, &retlen, unary);
  // printf("len: %c = %d: ", lexret.chr, retlen);
  // print_lexem(lexret);

  char *str1 = "-3";
  pars_lexeme(str1, &lexret, &retlen, unary);
  // printf("len: %c = %d: ", lexret.chr, retlen);
  // print_lexem(lexret);

  ck_assert_int_eq(retlen, 2);
}
END_TEST

/** @brief The test for the function str_to_polish.
 *
 *  Parses a string and saves to a queue.
 *
 *  @param str2que_test01 a test case.
 *
 *  @return void
 */
START_TEST(str2que_test01) {
  int size;
  char *expression = "-1+1+4^7mod3";
  que *converted;
  // que*
  str_to_polish(expression, &converted);

  size = converted->size;
  ck_assert_int_eq(size, 9);

  // todo(alex): the case with ))
  // char *expression2 = "1)";
  // str_to_polish(expression2, &converted);
  // printf("str(%s ) to polish que: \n", expression2);
  // queue_print(converted);
  // ck_assert_int_eq(converted->size, 0);
  queue_free(converted);
}
END_TEST

/** @brief The test for the function str_to_polish.
 *
 *  Parses a string and saves to a queue.
 *
 *  @param str2que_test02 a test case.
 *
 *  @return void
 */
START_TEST(str2que_test02) {
  int size;

  que *res0;
  char *str0 = "log(0.7)";
  str_to_polish(str0, &res0);
  // printf("str(%s ) to pilish que: \n", str0);
  size = res0->size;
  // queue_print(res0);
  queue_free(res0);
  ck_assert_int_eq(size, 2);
}
END_TEST

Suite *utils_suite(void) {
  Suite *suite = suite_create("utils suite");
  TCase *cases = tcase_create("utils case");

  tcase_add_test(cases, mstackest01);
  tcase_add_test(cases, queue_test01);
  tcase_add_test(cases, prior_test01);
  tcase_add_test(cases, rm_sp_test01);
  tcase_add_test(cases, valid_test01);
  tcase_add_test(cases, pars_funx_test01);
  tcase_add_test(cases, pars_num_test01);
  tcase_add_test(cases, pars_lexeme_test01);
  tcase_add_test(cases, str2que_test01);
  tcase_add_test(cases, str2que_test02);

  tcase_set_timeout(cases, 999999);
  suite_add_tcase(suite, cases);

  return suite;
}
