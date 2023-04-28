cmake_minimum_required(VERSION 3.22)
project(CPP1_s21_matrixplus)

set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_LIBRARY s21_matrix_oop)
set(TARGET_TEST tests)

set(MORE_CXX_FLAGS "-std=c++17")
set(TESTFILE_FLAGS "")

set(TEST_FLAGS -Wall -Werror -Wextra -g) #  -g #-static-libasan

if (EXT_TEST STREQUAL "1")
if (OS STREQUAL "Linux")
set(TEST_FLAGS -Wall -Werror -Wextra -Wpedantic -fsanitize=leak -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -g) # 
else()
set(TEST_FLAGS -Wall -Werror -Wextra -Wpedantic                 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -g)
endif()
endif()

set(COVERAGE_FLAGS --coverage) #  # -fprofile-arcs -ftest-coverage -lgcov 

set(SOURCE s21_matrix_plus.cc)
set(TEST_SOURCE tests.cc)

if (CMAKE_BUILD_TYPE STREQUAL "TEST")
    set(MORE_CXX_FLAGS ${MORE_CXX_FLAGS} ${TEST_FLAGS} ${COVERAGE_FLAGS})
    set(TESTFILE_FLAGS ${TESTFILE_FLAGS} ${TEST_FLAGS})
    set(CMAKE_CXX_COMPILER g++)
endif()

include_directories(.)

add_library(${TARGET_LIBRARY} STATIC ${SOURCE})

target_compile_options(${TARGET_LIBRARY} PRIVATE ${MORE_CXX_FLAGS}) # ${CMAKE_CXX_FLAGS}
target_compile_features(${TARGET_LIBRARY} PRIVATE cxx_std_17)
target_link_options(${TARGET_LIBRARY} PRIVATE ${MORE_CXX_FLAGS}) # ${CMAKE_CXX_FLAGS}

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${TARGET_TEST} ${TEST_SOURCE})
target_compile_features(${TARGET_TEST} PRIVATE cxx_std_17)
target_compile_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS}) # ${CMAKE_CXX_FLAGS}

if (CMAKE_BUILD_TYPE STREQUAL "TEST")
    target_link_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS} ${COVERAGE_FLAGS})
else()
    target_link_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS})
endif()

target_link_libraries(${TARGET_TEST} ${TARGET_LIBRARY} GTest::gtest_main)

