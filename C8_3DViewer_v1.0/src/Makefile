# Commmon
.PHONY: all clean check test 
CC = gcc -Wall -Wextra -Werror -std=c11 -g
DEBUG_FLAG = -fsanitize=address
TEST = test.out
TARGET = 3d_viewer

# Check for OS
ifeq ($(shell uname -s), Darwin)
        LEAKS=leaks --atExit -- ./$(TEST)
		COVERAGE_FLAG:= --coverage # -L.
		CHECK_LIB = -lcheck
#		OS_FLAG = -D MAC
define PRESET
		brew install check 
                brew install clang-format 
                brew install cppcheck 
                brew install qt 
                brew install --cask mactex
endef
else
        LEAKS=CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST) #--log-file=RESULT_VALGRIND.txt | grep -i leaks RESULT_VALGRIND.txt  
		COVERAGE_FLAG:=-fprofile-arcs -ftest-coverage 
		CHECK_LIB = -lcheck -lcheck_pic -lsubunit -pthread -lrt -lm
#		OS_FLAG = -D LINUX
define PRESET
		sudo apt install check clang-format cppcheck qt5-default texlive-full
endef
endif


# Utilities
check: tests
	@cp ../materials/linters/.clang-format . 
	@clang-format -n *.c *.h *.cpp
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h *.cpp 
	@$(LEAKS)

preset:
	$(PRESET)

# Demanding targets regardng SOW
all: tests gcov

clean: 
	@cp ../materials/linters/.clang-format . 
	@clang-format -i *.c *.h
	@rm -rf *.gcno *.gcda *.info *.{a,o,dSYM,out} .clang-format 
	@rm -f docs/text.log docs/text.aux docs/text.pdf docs/text.toc  
	@rm -rf build report
	@rm -f $(TARGET).tgz
	@rm -f *.o *.a $(TEST) gcov_test
	@if [ -f viewer/Makefile ]; then \
	    make -C viewer clean; \
	fi 
	@rm -rf viewer/Makefile viewer/3D_Viewer.app

tests:
	@$(CC) -c model.c -o model.o 
	@ar rcs model.a model.o
	@ranlib model.a
	@$(CC) -c s21_matrix.c -o s21_matrix.o
	@ar rcs s21_matrix.a s21_matrix.o
	@ranlib s21_matrix.a
	@$(CC) -c test.c -o test.o
	@$(CC) $(OS_FLAG) $(DEBUG_FLAG) test.o model.a s21_matrix.a $(CHECK_LIB) -o $(TEST) 	 
	@./$(TEST) 

dvi:
	@latex -output-directory=./docs ./docs/text.tex

install:
	make clean
	mkdir -p ../build
	cd viewer && qmake && make && make clean && rm Makefile && cp -R 3D_Viewer.app ../../build

uninstall:
	@rm -rf ../build

dist: clean
	@mkdir dist/
	@cp -r docs/ dist/docs
	@cp -r viewer dist/
	@cp Makefile dist/Makefile
	@cp *.c dist/
	@cp *.h dist/
	@tar czf $(TARGET).tgz dist/
	@rm -rf dist/

gcov: tests
	@$(CC) $(COVERAGE_FLAG) $(OS_FLAG) test.c model.c s21_matrix.a $(CHECK_LIB) -o gcov_test	
	@./gcov_test
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	@genhtml -o report/ gcov_test.info
	open report/index.html
