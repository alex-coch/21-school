CFLAGS:=-Wall -Werror -Wextra -std=c11 -g
# ASAN=-g 
TARGET=s21_matrix.a
INC:=$(shell find . -maxdepth 1 -name "*.h")
SRC:=$(shell find . -maxdepth 1 -name "s21*.c")
OBJS:=$(SRC:%.c=%.o)
TEST_LIBS:=$(shell pkg-config --cflags --libs check) 
TARGET_TEST=test
TARGET_TEST_LIB=s21_matrix_test.a
TEST_DIR=./tests
TEST_SRC:=$(shell find $(TEST_DIR) -name "*.c")
TEST_INC:=$(shell find $(TEST_DIR) -name "*.h")
TEST_OBJS:=$(TEST_SRC:%.c=%.o)
OS = $(shell uname)

ifeq ($(OS), Darwin)
        LEAKS=leaks --atExit -- test
		GCOV_FLAGS:= --coverage # -L.
		TEST_LIBS = -lcheck
else
        LEAKS=CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test #--log-file=RESULT_VALGRIND.txt | grep -i leaks RESULT_VALGRIND.txt  
		GCOV_FLAGS:=-fprofile-arcs -ftest-coverage $(ASAN)
		TEST_LIBS = -lcheck -lsubunit -pthread -lrt -lm
endif

all: gcov_report $(TARGET)

$(TARGET): $(OBJS)
	@ar -vrcs $(TARGET) $(OBJS)
	@ranlib $(TARGET)

$(OBJS): %.o:%.c $(SRC) $(INC)
	gcc $(CFLAGS) -o $@ -c $< $(ASAN)

test: CFLAGS+=$(GCOV_FLAGS)
test: $(TEST_OBJS) $(TARGET_TEST_LIB)
	gcc $(CFLAGS) main.c -o $@ $^ $(TEST_LIBS) 
	@./test

$(TEST_OBJS): $(TEST_DIR)%.o:$(TEST_DIR)%.c $(TEST_INC) main.c
	gcc $(CFLAGS) -o $@ -c $<

$(TARGET_TEST_LIB): $(OBJS) $(INC)
	@ar rc $(TARGET_TEST_LIB) $(OBJS)
	@ranlib $(TARGET_TEST_LIB)	

gcov_report: $(TARGET_TEST)
	@gcov $(TEST_SRC) $(SRC)
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory coverage

open:
	@open coverage/index.html

clean:
	@cp ../materials/linters/.clang-format . && cp ../materials/linters/.clang-format tests/ 
	@clang-format -i *.c *.h
	@rm -rf *.o test_* test-* *.a test tests/*.gc* *.gc* tests/*.o coverage *.info .clang-format tests/.clang-format
	

check:
	@cp ../materials/linters/.clang-format . && cp ../materials/linters/.clang-format tests/
	@clang-format -n *.c *.h
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h tests/*.c tests/*.h 
	@$(LEAKS)

.PHONY: all clean open
