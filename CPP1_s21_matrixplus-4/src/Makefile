BUILD_DIR="build"
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
		LEAKS=leaks --atExit -- ./build/tests
else
		LEAKS=CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./build/tests # --verbose  
endif

all: s21_matrix_oop.a

clean:
	@for d in $(shell find . -type d); do ( cp ../materials/linters/.clang-format $$d; ); done
	@clang-format -i $(shell find . -name "*\.cc" -or -name "*\.h")
	@find . -type f -name ".clang-format" -delete 
	@-rm -rf $(BUILD_DIR)

test:
	@cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=TEST -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
	@make -C $(BUILD_DIR) tests
	@./$(BUILD_DIR)/tests
	@geninfo $(shell find . -name '*.gcda' -or -name '*.gcno') . -o ./$(BUILD_DIR)/info
	@genhtml ./$(BUILD_DIR)/info -o ./$(BUILD_DIR)/coverage
	@open $(BUILD_DIR)/coverage/index.html

s21_matrix_oop.a:
	@cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF -DOS=$(OS)
	@make -C $(BUILD_DIR) s21_matrix_oop

check: clean test
	@for d in $(shell find . -type d); do ( cp ../materials/linters/.clang-format $$d; ); done
	@clang-format -n $(shell find . -not \( -path ./build -prune \) -name "*\.cc" -or -name "*\.h")
	$(LEAKS)

check-ext: clean
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=TEST -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF -DEXT_TEST=1
	make -C $(BUILD_DIR) tests

.PHONY: all clean test s21_matrix_oop.a check check-ext