CC = gcc -std=c11 -Wall -Wextra -Werror
target = s21_calc

MATH_LIB = -lm -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz\
 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -rdynamic

# CHECK_LIB = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
# COVERAGE_FLAG = -fprofile-arcs -ftest-coverage # -g
ifeq ($(OS), Darwin)
        LEAKS=leaks --atExit -- test.out
		COVERAGE_FLAG:= --coverage # -L.
		CHECK_LIB = -lcheck
else
        LEAKS=CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test.out #--log-file=RESULT_VALGRIND.txt | grep -i leaks RESULT_VALGRIND.txt  
		COVERAGE_FLAG:=-fprofile-arcs -ftest-coverage 
		CHECK_LIB = -lcheck -lcheck_pic -lsubunit -pthread -lrt -lm
endif

DEBUG_FLAG = -g # -fsanitize=address

# FOLDERS
INCLUDE_PATH = -I. -I./unit_tests -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0\
 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include\
  -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0\
   -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo\
    -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16\
    -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0\
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
BUILD_DIR = ./build
calc_DIR = ./
TEST_DIR = ./unit_tests
calc_OBJ_DIR = $(BUILD_DIR)/${target}
TEST_OBJ_DIR = $(BUILD_DIR)/test


# CREATE CALC FILES
calc_SOURCE =\
	stack.c\
	stack_queue.c\
	pars.c\
	calc.c\
	main.c\
	callbacks.c\

calc_OBJ = $(calc_SOURCE:%.c=%.o)
calc_OBJ_PATH = $(addprefix $(calc_OBJ_DIR)/, $(calc_OBJ))
calc_DEP_PATH = $(calc_OBJ_PATH:%.o=%.d)
-include $(calc_DEP_PATH)

$(calc_OBJ_DIR): 
	mkdir $@
$(TEST_OBJ_DIR):
	mkdir $@


# CREATE TEST FILES
TEST_SOURCE =\
	main.c\
	utils_suite.c\
	calc_suite.c\

TEST_OBJ = $(TEST_SOURCE:%.c=%.o) stack.o stack_queue.o pars.o calc.o
TEST_OBJ_PATH = $(addprefix $(TEST_OBJ_DIR)/, $(TEST_OBJ))
TEST_DEP_PATH = $(TEST_OBJ_PATH:%.o=%.d)
-include $(calc_DEP_PATH)

 
# ALL TARGET : all, tests, gcov_report, install, uninstall,clean, dvi, dist,
all: clean s21_calc tests
#	 ./s21_calc

install: clean s21_calc
	@mkdir ../install/
	@cp -r UI/ ./../install/UI
	@cp s21_calc ./../install

uninstall:
	@rm -rf .././install/

dist: clean
	@mkdir dist/
	@cp -r docs/ dist/docs
	@cp -r simple_grapher/ dist/simple_grapher
	@cp -r build/ dist/build
	@cp -r UI/ dist/UI
	@cp -r unit_tests/ dist/unit_tests
	@cp Makefile dist/Makefile
	@cp *.c dist/
	@cp *.h dist/
	@tar cvzf calc_dist.tgz dist/
	@rm -rf dist/

dvi:
	latex -output-directory=./docs ./docs/text.tex

# S21_CALC BUILD
$(calc_OBJ_DIR)/%.o: $(calc_DIR)/%.c
ifeq ($(OS), Darwin)
	$(CC) -c $(DEBUG_FLAG) $(EXTRA_WARNING) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` $< -o $@
else
	@$(CC) $(INCLUDE_PATH) $(MATH_LIB) $(DEBUG_FLAG) -MD -c $< -o $@ 
endif

$(BUILD_DIR)/libgrapher.a:
	@make -C ./simple_grapher libgrapher.a
	@cp simple_grapher/libgrapher.a $(BUILD_DIR)

s21_calc: $(calc_OBJ_PATH) $(BUILD_DIR)/libgrapher.a
ifeq ($(OS), Darwin)
	$(CC) -o $@  $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) $^ `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
else
	@$(CC) -o $@ $(INCLUDE_PATH) $(DEBUG_FLAG) $^ $(MATH_LIB) # $(CHECK_LIB)
endif

# S21_TEST.OUT BUILD
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
ifeq ($(OS), Darwin)
	$(CC) $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) -c `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` $< -o $@
else
	@$(CC) $(INCLUDE_PATH) $(MATH_LIB) $(CHECK_LIB) $(DEBUG_FLAG) -MD -c $< -o $@
endif

$(TEST_OBJ_DIR)/%.o: %.c
ifeq ($(OS), Darwin)
	$(CC) $(COVERAGE_FLAG) $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` $< -o $@
else
	@$(CC) $(COVERAGE_FLAG) $(INCLUDE_PATH) $(MATH_LIB) $(CHECK_LIB) $(DEBUG_FLAG) -MD -c $< -o $@
endif

test.out: $(TEST_OBJ_PATH)
ifeq ($(OS), Darwin)
	$(CC) $^ $(COVERAGE_FLAG) $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) -o test.out
else
	@$(CC) $^ $(COVERAGE_FLAG) $(INCLUDE_PATH) $(MATH_LIB) $(CHECK_LIB) $(DEBUG_FLAG) -o $@
endif

# TESTS COVERAGE
gcov_report: test.out	
	@./$<
	@lcov -t "$<" -o gcovreport.info -c -d $(TEST_OBJ_DIR)
	@genhtml -o $@ gcovreport.info

tests: test.out
#clear
	@./test.out

# CLEAN TARGET
clean:
	@find . -type f -name "*.o" -delete
	@find . -type f -name "*.d" -delete
	@find . -type f -name "*.a" -delete
	@find . -name "*.out" -delete
	@find . -name "*.gcno" -delete
	@find . -name "*.gcda" -delete
	@rm -rf ./gcov_report
	@rm -rf report
	@rm -rf gcovreport.info
	@rm -rf gcovreport
#	@rm -rf CPPLINT.cfg
	@rm -rf .././install/
	@rm -rf dist/
	@rm -rf calc_dist
	@rm -rf calc_dist.tgz
	@rm -rf s21_calc
	@rm -rf dist/simple_grapher
	@rm -f docs/text.aux docs/text.pdf docs/text.dvi docs/text.log docs/text.toc
	@cp ../materials/linters/.clang-format . && cp ../materials/linters/.clang-format simple_grapher/ && cp ../materials/linters/.clang-format unit_tests/
	@clang-format -i *.c *.h simple_grapher/*.c simple_grapher/*.h unit_tests/*.c unit_tests/*.h
	@find . -type f -name ".clang-format" -delete 

#RUN CPP CHECK
# cppcheck:
# 	cppcheck ${calc_SOURCE}

# RUN LINTER
# CPPLINT.cfg:
# 	cp ../materials/linters/CPPLINT.cfg .

check: 
	@cp ../materials/linters/.clang-format . && cp ../materials/linters/.clang-format simple_grapher/ && cp ../materials/linters/.clang-format unit_tests/
	@clang-format -n *.c *.h simple_grapher/*.c simple_grapher/*.h unit_tests/*.c unit_tests/*.h
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h simple_grapher/*.c simple_grapher/*.h unit_tests/*.c unit_tests/*.h 
	@$(LEAKS)

# PHONY TARGET
PHONY: check all install uninstall clean dvi dist tests gcov_report #prog fsan fval linter

# PERSONAL TARGETS SHOULD BE WRITTEN BELLOW, FOUND TARGETS ABOVE WILL BE DELETED
# clear:
# 	clear

# jdreama targets
# 2all: clear clean check cppcheck gcov_report

# jd: clean clear all
