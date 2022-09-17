ifeq ($(OS), Darwin)
        D_OS=
else
        D_OS=-D_OS_LINIX
endif

CC=gcc -std=c11 -D_GNU_SOURCE -Wall -Wextra -Werror $(D_OS)
CH=grep/*.h grep/*.c cat/*.c cat/*.h

all: clean s21_cat s21_grep test test-check

s21_cat:
	@$(CC) cat/s21_cat.c -o cat/s21_cat

s21_grep:
	@$(CC) grep/s21_grep.c -o grep/s21_grep

clean:
	@rm -rf *.txt *.log *.cfg cat/*.log cat/*.cfg grep/*.log grep/*.cfg cat/s21_cat  grep/s21_grep cat/0* 0*

test: 
	@./cat.sh
	@python cat_unit.py

rebuild: clean all

check:
	@cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem $(CH)  #  --bug-hunting
	@cp ../materials/linters/CPPLINT.cfg cat/
	@cp ../materials/linters/CPPLINT.cfg grep/
	@python3 ../materials/linters/cpplint.py --extension=c $(CH)

test-check: 
	@./cat-ex.sh