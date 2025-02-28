CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -Wuninitialized -fpermissive
CLIBS  = -lgtest -lgtest_main

all: test

clean:
	rm -f *.a *.gcda *.gcno
	rm -rf build

test: clean s21_containers.h
	mkdir -p build
	$(CC) $(CFLAGS) set_tests.cc -o build/tests $(CLIBS)
	./build/tests

s21_containers.o: clean
	mkdir -p build
	$(CC) $(CFLAGS) s21_containers.h -o build/s21_containers.o

gcov-report: CFLAGS+= --coverage
gcov-report: test
	lcov -t "tests" -o ./build/gcov-report.info -c -d . --no-external
	genhtml -o ./build/report ./build/gcov-report.info
	#open ./build/report/index.html

googlestyle:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*.h ./*.cc
	rm -f ./.clang-format

clang-format:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.h ./*.cc
	rm -f ./.clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 --language=c++ ./*.h #./*.cc

valgrind: CFLAGS+= -g
valgrind: test
	valgrind --leak-check=full --leak-resolution=high -s -q ./build/tests

leaks: test
	CK_FORK=no leaks -atExit -- ./build/tests

