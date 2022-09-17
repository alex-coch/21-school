ifeq ($(OS), Darwin)
        D_OS=
else
        D_OS=-D_OS_LINIX
endif

CC=gcc -std=c11 -D_GNU_SOURCE -Wall -Wextra -Werror $(D_OS)
CH=*.c *.h

all: clean s21_cat 

s21_cat:
	@$(CC) s21_cat.c -o s21_cat

clean:
	@rm -rf *.txt *.log *.cfg *.log *.cfg *.log *.cfg s21_cat  /0* 0*

rebuild: clean all

check:
	@cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem $(CH)  #  --bug-hunting
	@cp ../../materials/linters/CPPLINT.cfg .
	@python3 ../../materials/linters/cpplint.py --extension=c $(CH)
