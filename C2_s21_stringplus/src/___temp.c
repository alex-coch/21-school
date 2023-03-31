#include <check.h>
#include <string.h>
#include "s21_sprintf.h"

START_TEST(sprintf_test_d) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    long int n = 3;
    res1 = s21_sprintf(str1, "%d", n);
    res2 = sprintf(str2, "%d", n);
    printf("\nint_s21: %s\n", str1);
    printf("int_std: %s\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(sprintf_test_c) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    res1 = s21_sprintf(str1, "%c %c", 'T', '@');
    res2 = sprintf(str2, "%c %c", 'T', '@');
    printf("char_s21: %s\n", str1);
    printf("char_std: %s\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(sprintf_test_i) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    short int n = 11;
    res1 = s21_sprintf(str1, "%i %i %i", n, -46, 57);
    res2 = sprintf(str2, "%i %i %i", n, -46, 57);
    printf("i_int_s21: %s\n", str1);
    printf("i_int_std: %s\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST
START_TEST(sprintf_test_f) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    float n = 7.46861;
    res1 = s21_sprintf(str1, "%15f %34.3f %50lf %+f", n, n, n, n);
    printf("float_s21: %s\n", str1);
    res2 = sprintf(str2, "%15f %34.3f %50lf %+f", n, n, n, n);
    printf("float_std: %s\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST
START_TEST(sprintf_test_f1) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    float n = -7.56864;
    res1 = s21_sprintf(str1, "%.50f", n);
    printf("float_s21: %s\n", str1);
    res2 = sprintf(str2, "%.50f", n);
    printf("float_std: %s\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST
START_TEST(sprintf_test_s) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    res1 = s21_sprintf(str1, "%s %s %s", "Hello", " world", "!");
    res2 = sprintf(str2, "%s %s %s", "Hello", " world", "!");
    printf("string_s21: %s\n", str1);
    printf("string_std: %s\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST
START_TEST(sprintf_test_u) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    unsigned short n = 2;
    unsigned long m = 33;
    res1 = s21_sprintf(str1, "%u %u %u", n, m, (unsigned)58432322);
    res2 = sprintf(str2, "%u %u %u", n, m, (unsigned)58432322);
    printf("u_int_s21: %s\n", str1);
    printf("u_int_std: %s\n\n", str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(SPRINTFTestdogletho242) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*u\n", 15, 152352352);
    s21_sprintf(str1, "|%0*u\n", 15, 152352352);
    ck_assert_pstr_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho49) {
    char str[100];
    char str1[100];
    sprintf(str, "|%0*.*d|\n", 18, 15, -152352352);
    s21_sprintf(str1, "|%0*.*d|\n", 18, 15, -152352352);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho50) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-010d|", 18);
    s21_sprintf(str1, "|%-010d|", 18);
    ck_assert_str_eq(str, str1);

}
END_TEST

START_TEST(SPRINTFTestdogletho51) {
    char str[100];
    char str1[100];
    sprintf(str, "|%-10.5d|", 18);
    s21_sprintf(str1, "|%-10.5d|", 18);
    ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho66) {
    char c[255] = {}, d[255] = {};
    int n = 2100, n1 = 0, n2 = -21;
    s21_sprintf(c, "%-10d %010d %-010d %*d%-5d", 21, n2, n, 10, n, n2);
    sprintf(d, "%-10d %010d %-010d %*d%-5d", 21, n2, n, 10, n, n2);
    ck_assert_str_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestdogletho67) {
    char c[255] = {}, d[255] = {};
    int n = 2100, n1 = 0, n2 = -21;
    s21_sprintf(c, "%-10d %010d", 21, n2, n);
    sprintf(d, "%-10d %010d", 21, n2, n);
    ck_assert_str_eq(c, d);
}
END_TEST

START_TEST(STRNCMPTest7) {
    char *str1 = "test\0abc";
    char *str2 = "test\0";
    ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5), "Failed on 7");
}
END_TEST

START_TEST(MEMCMPTest10) {
    char str1[] = "t\000";
    char str2[] = "t\0";
    int n = 2;
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_sprintf_d) {
    short length = 50;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    long int n = 3;
    res1 = s21_sprintf(str1, "%ld%*.5d  % d   %+d %*d%-2d", n, -2, 3, 2, 46,
    4, -53, 9);
    res2 = sprintf(str2, "%ld%*.5d  % d   %+d %*d%-2d", n, -2, 3, 2, 46,
    4, -53, 9);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST
START_TEST(test_sprintf_zvezd) {
    char c[255] = {}, d[255] = {}, x1 = 't';
    int n = 2100, n1 = 0, n2 = -21;

    s21_sprintf(c, "|%0*.*d|", 20, 25, n);
    sprintf(d, "|%0*.*d|", 20, 25, n);
    ck_assert_str_eq(c, d);
}
END_TEST

int main() {
    Suite *s1 = suite_create("s21_string: ");
    TCase *tc1_1 = tcase_create("s21_string: ");
    SRunner *sr = srunner_create(s1);
    int result;
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, sprintf_test_d);
    tcase_add_test(tc1_1, sprintf_test_c);
    tcase_add_test(tc1_1, sprintf_test_i);
    tcase_add_test(tc1_1, sprintf_test_f);
    tcase_add_test(tc1_1, sprintf_test_f1);
    tcase_add_test(tc1_1, sprintf_test_s);
    tcase_add_test(tc1_1, sprintf_test_u);
    tcase_add_test(tc1_1, SPRINTFTestdogletho242);
    tcase_add_test(tc1_1, SPRINTFTestdogletho49);
    tcase_add_test(tc1_1, SPRINTFTestdogletho66);
    tcase_add_test(tc1_1, SPRINTFTestdogletho67);
    tcase_add_test(tc1_1, STRNCMPTest7);
    tcase_add_test(tc1_1, test_sprintf_d);
    tcase_add_test(tc1_1, MEMCMPTest10);
    tcase_add_test(tc1_1, test_sprintf_zvezd);

    tcase_add_test(tc1_1, SPRINTFTestdogletho50);
    tcase_add_test(tc1_1, SPRINTFTestdogletho51);

    srunner_run_all(sr, CK_ENV);
    result = srunner_ntests_failed(sr);
    srunner_free(sr);
    return result == 0 ? 0 : 1;
}



