#include <check.h>
#include <string.h>
#include <ctype.h>
#include "s21_string.h"

START_TEST(test_strlen) {
    ck_assert_uint_eq(s21_strlen("hi"), strlen("hi"));
    ck_assert_uint_eq(s21_strlen(""), strlen(""));
    ck_assert_uint_eq(s21_strlen("Hello piople!"), strlen("Hello piople!"));
    ck_assert_uint_eq(s21_strlen("hello! \n hi!"), strlen("hello! \n hi!"));
    ck_assert_uint_eq(s21_strlen("hello! \0 hi!"), strlen("hello! "));
}
END_TEST

START_TEST(test_strchr) {
    char temp[10] = "abcdbc";
    char *temp2 = "";
    ck_assert_ptr_eq(s21_strchr(temp, 'b'), strchr(temp, 'b'));
    //ck_assert_str_eq(s21_strchr(temp, 'b'), strchr(temp, 'b'));
    ck_assert_ptr_eq(s21_strchr(temp, 'e'), strchr(temp, 'e'));
    ck_assert_ptr_eq(s21_strchr(temp2, 'b'), strchr(temp2, 'b'));
    ck_assert_ptr_eq(s21_strchr(temp, 0), strchr(temp, 0));
    //ck_assert_ptr_eq(s21_strchr(temp, 'e'), strchr(temp, 'e'));
}
END_TEST

START_TEST(test_strcmp) {
    char *temp = malloc(15);
    char *temp2 = malloc(15);
    memset(temp, 'i', 10);
    memset(temp2, 'i', 10);
    temp2[10] = '\0';
    temp[10] = '\0';
    ck_assert_int_eq(s21_strcmp(temp, temp2), strcmp(temp, temp2));
    temp2[0]='y';
    //printf("%d %d %s\n", s21_strcmp(temp, temp2), strcmp(temp, temp2), temp2);
    ck_assert_int_eq(s21_strcmp(temp, temp2), strcmp(temp, temp2));
    temp2[0]='a';
    //printf("%d %d %s\n", s21_strcmp(temp, temp2), strcmp(temp, temp2), temp2);
    ck_assert_int_eq(s21_strcmp(temp, temp2), strcmp(temp, temp2));
    ck_assert_int_eq(s21_strcmp(temp, ""), strcmp(temp, ""));
    ck_assert_int_eq(s21_strcmp("", temp2), strcmp("", temp2));
    free(temp2);
    free(temp);
}
END_TEST

START_TEST(test_strncmp) {
    char *temp = malloc(15);
    char *temp2 = malloc(15);
    memset(temp, 'i', 10);
    memset(temp2, 'i', 10);
    ck_assert_int_eq(s21_strncmp(temp, temp2, 2), strncmp(temp, temp2, 2));
    ck_assert_int_eq(s21_strncmp(temp, temp2, 10), strncmp(temp, temp2, 10));
    ck_assert_int_eq(s21_strncmp(temp, temp2, 0), strncmp(temp, temp2, 0));
    temp2[4]='y';
    ck_assert_int_eq(s21_strncmp(temp, temp2, 2), strncmp(temp, temp2, 2));
    ck_assert_int_eq(s21_strncmp(temp, temp2, 10), strncmp(temp, temp2, 10));
    ck_assert_int_eq(s21_strncmp(temp, "", 10), strncmp(temp, "", 10));
    ck_assert_int_eq(s21_strncmp("", temp2, 10), strncmp("", temp2, 10));
    free(temp2);
    free(temp);
}
END_TEST

START_TEST(test_strcat) {
    char temp[20], temp2[20];
    for (int i = 0; i < 20; i++) {
        temp[i] = '\0';
        temp2[i] = '\0';
    }
    ck_assert_str_eq(s21_strcat(temp, ""), strcat(temp2, ""));
    ck_assert_str_eq(s21_strcat(temp, "d"), strcat(temp2, "d"));
    ck_assert_str_eq(s21_strcat(temp, "v"), strcat(temp2, "v"));
    ck_assert_str_eq(s21_strcat(temp, "d"), strcat(temp2, "d"));
    ck_assert_str_eq(s21_strcat(temp, "1z"), strcat(temp2, "1z"));
    ck_assert_str_eq(s21_strcat(temp, "12"), strcat(temp2, "12"));
    ck_assert_str_eq(s21_strcat(temp, "\0"), strcat(temp2, "\0"));
}
END_TEST

START_TEST(test_strncat) {
    char temp[10], temp2[10];
    for (int i = 0; i < 10; i++) {
        temp[i] = '\0';
        temp2[i] = '\0';
    }
    ck_assert_str_eq(s21_strncat(temp, "", 0), strncat(temp2, "", 0));
    ck_assert_str_eq(s21_strncat(temp, "", 1), strncat(temp2, "", 1));
    ck_assert_str_eq(s21_strncat(temp, "vv", 1), strncat(temp2, "vv", 1));
    ck_assert_str_eq(s21_strncat(temp, "dvd", 1), strncat(temp2, "dvd", 1));
    ck_assert_str_eq(s21_strncat(temp, "", 1), strncat(temp2, "", 1));
    ck_assert_str_eq(s21_strncat(temp, "1z", 3), strncat(temp2, "1z", 3));
}
END_TEST

START_TEST(test_memchr) {
    char temp[6] = "abcdbc";
    char *temp2 = "";
    ck_assert_ptr_eq(s21_memchr(temp, 'b', 3), memchr(temp, 'b', 3));
    ck_assert_ptr_eq(s21_memchr(temp, 'e', 3), memchr(temp, 'e', 3));
    ck_assert_ptr_eq(s21_memchr(temp, 'e', 0), memchr(temp, 'e', 0));
    ck_assert_ptr_eq(s21_memchr(temp2, 500, 2), memchr(temp2, 500, 2));
    ck_assert_ptr_eq(s21_memchr(temp2, 500, 1), memchr(temp2, 500, 1));
    ck_assert_ptr_eq(s21_memchr(temp2, 'b', 10), memchr(temp2, 'b', 10));
    ck_assert_ptr_eq(s21_memchr(temp2, 0, 1), memchr(temp2, 0, 1));
    ck_assert_ptr_eq(s21_memchr(temp2, 0, 10), memchr(temp2, 0, 10));
}
END_TEST

START_TEST(test_memcmp) {
    char *temp1 = "RATATATA - RA TAATATATA 1234567890*&^%%$#@";
    char *temp2 = "RATATATA - RA TAATATATA 1234567890*&^%%$#@";
    char *temp21 = "RATAY";
    char *temp22 = "RATAB";
    ck_assert_msg(s21_memcmp(temp1, temp2, 256) == memcmp(temp1, temp2, 256),
    "1_failed.");
    ck_assert_msg(s21_memcmp(temp1, temp2, 2) == memcmp(temp1, temp2, 2),
    "2_failed.");
    ck_assert_msg(s21_memcmp(temp1, temp2, 123) == memcmp(temp1, temp2, 123),
    "3_failed.");
    ck_assert_msg(s21_memcmp(temp1, temp2, 36) == memcmp(temp1, temp2, 36),
    "4_failed.");
    ck_assert_msg(s21_memcmp(temp1, temp21, 5) == memcmp(temp1, temp21, 5),
    "5_failed.");
    ck_assert_msg(s21_memcmp(temp1, temp22, 5) == memcmp(temp1, temp22, 5),
    "6_failed.");
}
END_TEST

START_TEST(test_memset) {
    void *temp = malloc(10);
    void *temp2 = malloc(10);
    //s21_memset(temp, 'y', 10);
    //memset(temp2, 'y', 10);
    ck_assert_int_eq(s21_memcmp(s21_memset(temp, 'y', 10), memset(temp2, 'y', 10), 10), 0);
    //s21_memset(temp, '5', 4);
    //memset(temp2, '5', 4);
    ck_assert_int_eq(s21_memcmp(s21_memset(temp, '5', 4), memset(temp2, '5', 4), 4), 0);
    //s21_memset(temp, '\0', 10);
    //memset(temp2, '\0', 10);
    ck_assert_int_eq(s21_memcmp(s21_memset(temp, '\0', 10), memset(temp2, '\0', 10), 10), 0);
    ck_assert_int_eq(s21_memcmp(s21_memset(temp, 32, 0), memset(temp2, 32, 0), 0), 0);
    ck_assert_int_eq(s21_memcmp(s21_memset(temp, 65, 12), memset(temp2, 65, 12), 12), 0);
    //printf("%s", (char *) memset(temp2, 65, 12));
    free(temp2);
    free(temp);
}
END_TEST

START_TEST(test_memcpy) {
    char *arr1 = "GG_WP MEN";
    void* temp1 = calloc(100, sizeof(char*));
    void* temp2 = calloc(100, sizeof(char*));
    ck_assert_int_eq(s21_memcmp(s21_memcpy(temp1, arr1, 5), memcpy(temp2, arr1, 5), 5), 0);
    free(temp1);
    free(temp2);
    char *arr2 = "";
    void *temp3 = calloc(100, sizeof(char*));
    void *temp4 = calloc(100, sizeof(char*));
    ck_assert_int_eq(s21_memcmp(s21_memcpy(temp3, arr2, 5), memcpy(temp4, arr2, 5), 5), 0);
    free(temp3);
    free(temp4);
    char *arr3 = "RA TA TA TA - RA TAATATATA";
    void *temp5 = calloc(100, sizeof(char*));
    void *temp6 = calloc(100, sizeof(char*));
    ck_assert_int_eq(s21_memcmp(s21_memcpy(temp5, arr3, 10), memcpy(temp6, arr3, 10), 10), 0);
    free(temp5);
    free(temp6);
    char *arr4 = "1234567890*&^%%$#@!";
    void *temp7 = calloc(100, sizeof(char*));
    void *temp8 = calloc(100, sizeof(char*));
    ck_assert_int_eq(s21_memcmp(s21_memcpy(temp7, arr4, 10), memcpy(temp8, arr4, 10), 10), 0);
    free(temp7);
    free(temp8);
}
END_TEST

START_TEST(test_memmove) {
    char *temp = malloc(30);
    char *temp1 = malloc(30);
    char *temp2 = "1234567890_school_21";
    ck_assert_int_eq(s21_memcmp(s21_memmove(temp, temp2, 10), memmove(temp1, temp2, 10), 10), 0); 
    ck_assert_int_eq(s21_memcmp(s21_memmove(temp, temp2, 20), memmove(temp1, temp2, 20), 20), 0);
    ck_assert_int_eq(s21_memcmp(s21_memmove(temp, temp2, 0), memmove(temp1, temp2, 0), 0), 0);
    ck_assert_int_eq(s21_memcmp(s21_memmove(temp, temp2, s21_strlen(temp2)), memmove(temp1, temp2, s21_strlen(temp2)), s21_strlen(temp2)), 0);
//    s21_memmove(temp, temp2, 10);
//    ck_assert_int_eq(memcmp(temp, temp2, 10), 0);
//    s21_memmove(temp, temp2, 20);
//    ck_assert_int_eq(memcmp(temp, temp2, 20), 0);
//    s21_memmove(temp, temp2, 0);
//    ck_assert_int_eq(memcmp(temp, temp2, 0), 0);
    free(temp);
    free(temp1);
}
END_TEST

START_TEST(test_s21_strcpy) {
    char *temp = malloc(50), *temp1 = malloc(50);
    char *temp2 = "1234567890";
    ck_assert_str_eq(s21_strcpy(temp, temp2), strcpy(temp1, temp2));
    ck_assert_str_eq(s21_strcpy(temp, ""), strcpy(temp1, ""));
    ck_assert_str_eq(s21_strcpy(temp, "123456789000"), strcpy(temp1, "123456789000"));
    free(temp);
    free(temp1);
}
END_TEST

START_TEST(test_strncpy) {
    char str1[30] = "Hello";
    char str2[] = " World";
    //int n = 6;
    ck_assert_str_eq(s21_strncpy(str1, str2, 6), strncpy(str1, str2, 6));
    //n = 4;
    ck_assert_str_eq(s21_strncpy(str1, str2, 4), strncpy(str1, str2, 4));
    char str3[30] = "";
    char str4[] = " HELLO";
    ck_assert_str_eq(s21_strncpy(str3, str4, 5), strncpy(str3, str4, 5));
    char str5[30] = "HI, ";
    char str6[] = " HELL\0O";
    ck_assert_str_eq(s21_strncpy(str5, str6, 5), strncpy(str5, str6, 5));
    char str7[30] = "HI, ";
    char str8[] = " HELLO";
    ck_assert_str_eq(s21_strncpy(str7, str8, 20), strncpy(str7, str8, 20));
}
END_TEST

START_TEST(test_strcspn) {
    ck_assert_uint_eq(s21_strcspn("aaaOOO", "O"), strcspn("aaaOOO", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOaa", "O"), strcspn("aaaOOOaa", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOoo", "Oo"), strcspn("aaaOOOo", "Oo"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOoo", "Ooo"), strcspn("aaaOOOo", "Ooo"));
    ck_assert_uint_eq(s21_strcspn("", "O"), strcspn("", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOaa", ""), strcspn("aaaOOOaa", ""));
    ck_assert_uint_eq(s21_strcspn("aaaOOOWa", "a"), strcspn("aaaOOOWa", "a"));
}
END_TEST

START_TEST(test_strpbrk) {
    char *str1 = "aAaxxxx";
    ck_assert_ptr_eq(s21_strpbrk(str1, "ax"), strpbrk(str1, "ax"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "x"), strpbrk(str1, "x"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "xA"), strpbrk(str1, "xA"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "z"), strpbrk(str1, "z"));
    ck_assert_ptr_eq(s21_strpbrk(str1, ""), strpbrk(str1, ""));
    ck_assert_ptr_eq(s21_strpbrk("", "ax"), strpbrk("", "ax"));
}
END_TEST

START_TEST(test_strerror) {
    //printf("%s%s\n", s21_strerror(0), strerror(0));
    for (int i = 0; i < ERR_MAX; i++) {
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
}
END_TEST

START_TEST(test_strrchr) {
    char str[8]="abcdbc";
    char *empty_str = "";
    ck_assert_ptr_eq(s21_strrchr(str, 'b'), strrchr(str, 'b'));
    ck_assert_str_eq(s21_strrchr(str, 'b'), "bc");
    ck_assert_ptr_eq(s21_strrchr(str, 'e'), strrchr(str, 'e'));
    ck_assert_ptr_eq(s21_strrchr(empty_str, 'b'), strrchr(empty_str, 'b'));
    ck_assert_ptr_eq(s21_strrchr(str, 0), strrchr(str, 0));
    ck_assert_ptr_eq(s21_strrchr(str, '\n'), strrchr(str, '\n'));
}
END_TEST

START_TEST(test_strspn) {
    ck_assert_uint_eq(s21_strspn("aaaOOO", "O"), strspn("aaaOOO", "O"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaa", "O"), strspn("aaaOOOaa", "O"));
    ck_assert_uint_eq(s21_strspn("", "O"), strspn("", "O"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaa", ""), strspn("aaaOOOaa", ""));
    ck_assert_uint_eq(s21_strspn("aaaOOOaaPPP", "Oa"), strspn("aaaOOOaaPPP", "Oa"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaaPPP", "aO"), strspn("aaaOOOaaPPP", "aO"));
}
END_TEST

START_TEST(test_strstr) {
    char str1[10] = "hello";
    char str2[10] = "he";
//    ck_assert_msg(s21_strstr("he", "h") == strstr("he", "h"), "failed");
    ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
    ck_assert_msg(s21_strstr(str1, " ") == strstr(str1, " "), "failed");
    ck_assert_msg(s21_strstr(str1, "qw") == strstr(str1, "qw"), "failed");
    ck_assert_msg(s21_strstr("hello", "hellp") == strstr("hello", "hellp"), "failed");
    ck_assert_msg(s21_strstr("hello sweet hello", "hellp") == strstr("hello sweet hello", "hellp"), "failed");

    char str11[1024] = "hello sweet hello";
    char str22[10] = "hello";
    char str33[1024] = "hello sweet hello";
    char str44[10] = "hello";

    ck_assert_msg(s21_strstr(str11, str22) == strstr(str11, str22), "failed");
    //printf("'%s' '%s'\n", s21_strstr(str11, str22), strstr(str33, str44));
}
END_TEST

START_TEST(test_strtok) {
    char str0[30] = "test1/test2/test3/test4";
    char delim = ',';
    ck_assert_msg(s21_strtok(str0, &delim) == strtok(str0, &delim), "failed");
    ck_assert_msg(s21_strtok(str0, &delim) == strtok(str0, &delim), "failed");
    delim = 'e';
    ck_assert_msg(s21_strtok(str0, &delim) == strtok(str0, &delim), "failed");
    char str2[30] = "AadacAdxa";
    delim = 'a';
    ck_assert_msg(s21_strtok(str2, &delim) == strtok(str2, &delim), "failed");
    char str3[30] = "ased dse c sze wsew";
    delim = 'e';
    ck_assert_msg(s21_strtok(str3, &delim) == strtok(str3, &delim), "failed");

   char str [24]="test1/test2/test3/test4", s21_str[24]="test1/test2/test3/test4", sep [10]="/", *istr, *s21_istr;
   istr = strtok(str,sep);
   s21_istr = s21_strtok(s21_str,sep);
   while (istr != NULL)
   {
  //    printf ("%s%s\n",istr, s21_istr);
      //ck_assert_msg(istr == s21_istr, "failed");
      //ck_assert_ptr_eq(istr, s21_istr);
      ck_assert_int_eq(s21_strcmp(istr, s21_istr), 0);
//      if (istr == s21_istr)
//	printf("111");
  //    else
//	printf("222");
      istr = strtok(NULL, sep);
      s21_istr = s21_strtok(NULL, sep);

//    char* str = NULL;
  //  char* s21_str = NULL;
    //char delim = '/';
    //ck_assert_ptr_eq(s21_strtok(s21_str, &delim), strtok(str, &delim));
    //printf("'%s' '%s'\n", s21_strtok(s21_str, &delim), strtok(str, &delim)); 
  }
    char* str4 = NULL;
    char* s21_str4 = NULL;
    char delim4 = '/';
    ck_assert_ptr_eq(s21_strtok(s21_str4, &delim4), strtok(str4, &delim4));
    //printf("strtok '%s' '%s'\n", s21_strtok(s21_str4, &delim4), strtok(str4, &delim4)); 

}
END_TEST

START_TEST(test_to_upper) {
    char *upper_str;
    upper_str = s21_to_upper("Hello, 123!");
    ck_assert_str_eq(upper_str, "HELLO, 123!");
    free(upper_str);
    upper_str = s21_to_upper("HELLO, 123!");
    ck_assert_str_eq(upper_str, "HELLO, 123!");
    free(upper_str);
    upper_str = s21_to_upper("");
    ck_assert_str_eq(upper_str, "");
    free(upper_str);
    upper_str = s21_to_upper(s21_NULL);
    ck_assert_ptr_eq(s21_to_upper(s21_NULL), NULL);
    free(upper_str);
}
END_TEST

START_TEST(test_to_lower) {
    char *lower_str;

    lower_str = s21_to_lower("Hello, 123!");
    ck_assert_str_eq(lower_str, "hello, 123!");
    free(lower_str);
    lower_str = s21_to_lower("hello, 123!");
    ck_assert_str_eq(lower_str, "hello, 123!");
    free(lower_str);
    lower_str = s21_to_lower("");
    ck_assert_str_eq(lower_str, "");
    free(lower_str);
    lower_str = s21_to_lower(s21_NULL);
    ck_assert_ptr_eq(s21_to_lower(s21_NULL), NULL);
    free(lower_str);
}
END_TEST

START_TEST(test_insert) {
    char *result;
    result = s21_insert("13", "2", 1);
    ck_assert_str_eq(result, "123");
    free(result);
    ck_assert_ptr_eq(s21_insert("", "2", 2), NULL);
    result = s21_insert("hello", "", 0);
    ck_assert_str_eq(result, "hello");
    free(result);
    result = s21_insert("hello", "", 2);
    ck_assert_str_eq(result, "hello");
    free(result);
    ck_assert_ptr_eq(s21_insert("hello", "", 6), NULL);
}
END_TEST

START_TEST(test_trim) {
    char str1[16] = "WoW\0, I love it!";
    char str2[2] = "W";
    char* str3 = (char *)s21_trim(str1, str2);
    ck_assert_str_eq(str3, "o");
    free(str3);
    char* str4 = (char *)s21_trim("WoW, I love it!", "P");
    ck_assert_str_eq(str4, "WoW, I love it!");
    free(str4);
    char* str5 = (char *)s21_trim("abc", "abc");
    ck_assert_str_eq(str5, "");
    free(str5);
}
END_TEST

START_TEST(test_sprintf_c) {
    short length = 50;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    res1 = s21_sprintf(str1, "%c %c %c %c %c %c %c %c", ' ', '#', '@', 65, 20, 300, -1, 0);
    res2 = sprintf(str2, "%c %c %c %c %c %c %c %c", ' ', '#', '@', 65, 20, 300, -1, 0);
    //printf("Error: %d %d '%s' '%s'\n", res1, res2, str1, str2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(test_sprintf_d) {
    short length = 50;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    long int n = 4;
    res1 = s21_sprintf(str1, "%ld%*.5d  % d   %+d %*d%-2.d", n, -1, 6, 2, 46,
    4, -53, 9);
    res2 = sprintf(str2, "%ld%*.5d  % d   %+d %*d%-2.d", n, -1, 6, 2, 46,
    4, -53, 9);
    printf("'%s' '%s' '%*.4d'\n", str1, str2, 8, 7);
    //s21_strcat(str1, " "); res2--;
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(test_sprintf_i) {
    short length = 50;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    short int n = 11;
    res1 = s21_sprintf(str1, "%hi %.i %0i %i", n, 7, 57, -9);
    res2 = sprintf(str2, "%hi %.i %0i %i", n, 7, 57, -9);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(test_sprintf_f) {
    short length = 150;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    float n = 7.85227;
    res1 = s21_sprintf(str1, "%15f %34.3f %50lf %+f", n, n, n, n);
    res2 = sprintf(str2,  "%15f %34.3f %50lf %+f", n, n, n, n);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(test_sprintf_s) {
    short length = 50;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    res1 = s21_sprintf(str1, "%.*s %.3s %s", -2, "Hello", " world", "!");
    res2 = sprintf(str2, "%.*s %.3s %s", -2, "Hello", " world", "!");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(test_sprintf_u) {
    short length = 50;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    unsigned short n = 2;
    unsigned long m = 33;
    res1 = s21_sprintf(str1, "%hu %lu %u", n, m, (unsigned)58432322);
    res2 = sprintf(str2, "%hu %lu %u", n, m, (unsigned)58432322);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(test_sprintf_e) {
    char data[200];
    char data1[200];
    long double i = 1.1e+49;
    s21_sprintf(data, "%Le", i);
    sprintf(data1, "%Le", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_E) {
    char data[200];
    char data1[200];
    long double i = 1.1e+49;
    s21_sprintf(data, "%LE", i);
    sprintf(data1, "%LE", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_x) {
    char data[30];
    char data1[30];
    unsigned short i = 300;
    s21_sprintf(data, "%hx", i);
    sprintf(data1, "%hx", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_X) {
    char data[30];
    char data1[30];
    unsigned short i = 300;
    s21_sprintf(data, "%hX", i);
    sprintf(data1, "%hX", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_o) {
    char data[30];
    char data1[30];
    unsigned short i = 144;
    s21_sprintf(data, "%ho", i);
    sprintf(data1, "%ho", i);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_0) {
    char data[30];
    char data1[30];
    s21_sprintf(data, "%0*.e", 10, 0.9);
    sprintf(data1, "%0*.e", 10, 0.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_g) {
    char data[30];
    char data1[30];
    s21_sprintf(data, "%g", 1000000.9);
    sprintf(data1, "%g", 1000000.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_G) {
    char data[30];
    char data1[30];
    s21_sprintf(data, "%G", 1000000.9);
    sprintf(data1, "%G", 1000000.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_resh) {
    char data[30];
    char data1[30];
    s21_sprintf(data, "%#05x", 21);
    sprintf(data1, "%#05x", 21);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_lc) {
    char data[5];
    char data1[5];
    s21_sprintf(data, "%c", 'c');
    sprintf(data1, "%c", 'c');
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_p) {
    char data[50];
    char data1[50];
    s21_sprintf(data, "01) standart PRINTF : |%p|\n", "salut");
    sprintf(data1, "01) standart PRINTF : |%p|\n", "salut");
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_n) {
    char data[30];
    char data1[30];
    int num;
    s21_sprintf(data, "%n", &num);
    sprintf(data1, "%n", &num);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sprintf_ee) {
    char data[30];
    char data1[30];
    s21_sprintf(data, "%e", 9999999999.9);
    sprintf(data1, "%e", 9999999999.9);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_sscanf_d) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    long ip1 = 1444499.666666;
    unsigned int ip2 = -7;
    s21_sscanf(str1, "%ud.%ld.%ud.%ld", &ip2, &ip1, &ip2, &ip1);
    sscanf(str2, "%ud.%ld.%ud.%ld", &ip2, &ip1, &ip2, &ip1);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_f) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    float temp = +7.944433;
    float temp2 = -0.9223348;
    s21_sscanf(str1, "%5f %2f", &temp, &temp2);
    sscanf(str2, "%5f %2f", &temp2, &temp2);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_s) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    float temp2;
    char temp3;
    s21_sscanf("GG '@' +4.148388 WP", "%5s %5f %5c", str1, &temp2, &temp3);
    sscanf("GG '@' +4.148388 WP", "%5s %5f %5c", str2, &temp2, &temp3);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_u) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    unsigned int temp2;
    unsigned long temp3;
    s21_sscanf("Hello 777 -300", "%5s %5u %5lX GG WP", str1, &temp2, &temp3);
    sscanf("Hello 777 -300", "%5s %5u %5lX GG WP", str2, &temp2, &temp3);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_e) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    long double temp2;
    long double temp3;
    s21_sscanf("Ho 1.1f+58 ho 1.1E+49 ho", "%5s %5Le %5LE GG WP", str1, &temp2, &temp3);
    sscanf("Ho 1.1f+58 ho 1.1E+49 ho ", "%5s %5Le %5LE GG WP", str2, &temp2, &temp3);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_i) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    short int temp = 11;
    int temp2 = 7;
    s21_sscanf("Bu ga ga ", "%5s %5hi %5i", str1, &temp, &temp2);
    sscanf("Bu ga ga ", "%5s %5hi %5i", str2, &temp, &temp2);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_x) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    unsigned long temp = -300;
    unsigned int temp2 = 7;
    s21_sscanf("Bu ga ga ", "%5s %5hx %5X", str1, &temp, &temp2);
    sscanf("Bu ga ga ", "%5s %5lx %5X", str2, &temp, &temp2);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_o) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    unsigned short temp = -3000;
    char temp2 = 'G';
    s21_sscanf("Ratatata", " %5s %5ho %5c", str1, &temp, &temp2);
    sscanf("Ratatata", " %5s %5ho %5c", str2, &temp, &temp2);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_p) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    char* temp = "salut";
    s21_sscanf("try try try", " %5s %% %5p", str1, &temp);
    sscanf("try try try", " %5s %% %5p", str2, &temp);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

START_TEST(test_sscanf_n) {
    short length = 30;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int temp;
    s21_sscanf("try try try", " %5s %n", str1, &temp);
    sscanf("try try try", " %5s %n", str2, &temp);
    ck_assert_str_eq(str1, str2);
    free(str2);
    free(str1);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("s21_string: ");
    TCase *tc1_1 = tcase_create("s21_string: ");
    SRunner *sr = srunner_create(s1);
    int result;
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_strlen);
    tcase_add_test(tc1_1, test_strchr);
    tcase_add_test(tc1_1, test_strcmp);
    tcase_add_test(tc1_1 , test_strncmp);
    tcase_add_test(tc1_1, test_strcat);
    tcase_add_test(tc1_1, test_strncat);
    tcase_add_test(tc1_1, test_memchr);
    tcase_add_test(tc1_1, test_memcmp);
    tcase_add_test(tc1_1, test_memset);
    tcase_add_test(tc1_1, test_memcpy);
    tcase_add_test(tc1_1, test_memmove);
    tcase_add_test(tc1_1, test_s21_strcpy);
    tcase_add_test(tc1_1, test_strncpy);
    tcase_add_test(tc1_1, test_strcspn);
    tcase_add_test(tc1_1, test_strpbrk);
    tcase_add_test(tc1_1, test_strerror);
    tcase_add_test(tc1_1, test_strrchr);
    tcase_add_test(tc1_1, test_strspn);
    tcase_add_test(tc1_1, test_strstr);
    tcase_add_test(tc1_1, test_strtok);
    tcase_add_test(tc1_1, test_to_upper);
    tcase_add_test(tc1_1, test_to_lower);
    tcase_add_test(tc1_1, test_insert);
    tcase_add_test(tc1_1, test_trim);
    tcase_add_test(tc1_1, test_sprintf_c);
    tcase_add_test(tc1_1, test_sprintf_d);
    tcase_add_test(tc1_1, test_sprintf_i);
    tcase_add_test(tc1_1, test_sprintf_f);
    tcase_add_test(tc1_1, test_sprintf_s);
    tcase_add_test(tc1_1, test_sprintf_u);
    tcase_add_test(tc1_1, test_sprintf_e);
    tcase_add_test(tc1_1, test_sprintf_E);
    tcase_add_test(tc1_1, test_sprintf_x);
    tcase_add_test(tc1_1, test_sprintf_X);
    tcase_add_test(tc1_1, test_sprintf_o);
    tcase_add_test(tc1_1, test_sprintf_0);
    tcase_add_test(tc1_1, test_sprintf_g);
    tcase_add_test(tc1_1, test_sprintf_G);
    tcase_add_test(tc1_1, test_sprintf_lc);
    tcase_add_test(tc1_1, test_sprintf_p);
    tcase_add_test(tc1_1, test_sprintf_resh);
    tcase_add_test(tc1_1, test_sprintf_n);
    tcase_add_test(tc1_1, test_sprintf_ee);
    tcase_add_test(tc1_1, test_sscanf_d);
    tcase_add_test(tc1_1, test_sscanf_s);
    tcase_add_test(tc1_1, test_sscanf_f);
    tcase_add_test(tc1_1, test_sscanf_u);
    tcase_add_test(tc1_1, test_sscanf_e);
    tcase_add_test(tc1_1, test_sscanf_i);
    tcase_add_test(tc1_1, test_sscanf_x);
    tcase_add_test(tc1_1, test_sscanf_o);
    tcase_add_test(tc1_1, test_sscanf_p);
    tcase_add_test(tc1_1, test_sscanf_n);
    srunner_run_all(sr, CK_ENV);
    result = srunner_ntests_failed(sr);
    srunner_free(sr);
    return result == 0 ? 0 : 1;
}
