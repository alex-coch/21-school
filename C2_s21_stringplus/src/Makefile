OS := $(shell uname -s)
CC = gcc
FLAG = -Wall -Werror -Wextra
FLAG_C = -c -Wall -Werror -Wextra
CL_11 = -std=c11 
BIBLIOTECKA = s21_string.c s21_sprintf.c

ifeq ($(OS), Darwin)
	PLATFORM := -lcheck
else
	PLATFORM := -lcheck -lsubunit -lrt -lm -lpthread -g
endif

all: clean s21_string.a test gcov_report 

s21_string.a:
	@$(CC) $(FLAG_C) $(CL_11) $(BIBLIOTECKA)
	@ar rcs s21_string.a s21_string.o s21_sprintf.o 

test: s21_string.a
	@$(CC) -c unit_test.c -o unit_test.o
#	@$(CC) -c test_02.c -o unit_test.o
	@$(CC) --coverage unit_test.o s21_string.a $(PLATFORM) -o testik.o
#	@./testik.o

gcov_report:
	@$(CC) --coverage $(BIBLIOTECKA) unit_test.c $(PLATFORM) -o gov_report.o
	@./gov_report.o
	@lcov -t s21_string_tests -o s21_string_tests.info -c -d .
	@genhtml -o report s21_string_tests.info

clean :
	@rm -f *.a
	@rm -f *.o
	@rm -f *.gcda
	@rm -f *.gcdo
	@rm -f *.gcno
	@rm -f *.info
