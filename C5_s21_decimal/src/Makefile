CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
SOURCES=s21_decimal.c
OBJECTS=$(SOURCES:.c=.o)
OS = $(shell uname)
TEST_FILE_NAME = test.c
TEST_FILE_NAME2 = test2.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: gcov_report

s21_decimal.a: clean $(OBJECTS)
	ar -rcs s21_decimal.a $(OBJECTS)
	rm -f *.o

test: $(TEST_FILE_NAME) s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

test2: $(TEST_FILE_NAME2) s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME2) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM
	clang-format -i *.c *.h

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
#	cp ../materials/linters/CPPLINT.cfg .
#	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
#	rm -rf CPPLINT.cfg
	clang-format -n *.c *.h
	make test

# style: test
# 	cp ../../materials/linters/CPPLINT.cfg ./
# 	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
# 	rm -f CPPLINT.cfg  

open:
	open report/index.html

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
