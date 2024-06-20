.PHONY: all test clean list

OS = $(shell uname -s)

CFLAGS= -std=c++17 -Wall -Wextra -Werror -g

GCOVFLAGS=-fprofile-arcs -ftest-coverage
LFLAGS=-lgcov --coverage
TEST_LIBS=-lgtest -lpthread
CC= g++

ARRAY_SRC= s21_array.h
VECTOR_SRC = s21_vector.h


all: test clean

.PHONY: test
test: map_test array_test vector_test list_test stack_test queue_test set_test multiset_test

map_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/map_test.cc -o map_test $(TEST_LIBS) 
	./map_test

list_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/test_list.cc -o test_list $(TEST_LIBS) 
	./test_list

stack_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/test_stack.cc -o test_stack $(TEST_LIBS) 
	./test_stack

queue_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/test_queue.cc -o test_queue $(TEST_LIBS) 
	./test_queue

array_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/test_array.cc -o test_array $(TEST_LIBS) 
	./test_array

vector_test: 
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(VECTOR_SRC) tests/test_vector.cc -o test_vector $(TEST_LIBS) 
	./test_vector

set_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/set_test.cc -o set_test $(TEST_LIBS)
	./set_test

multiset_test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(ARRAY_SRC) tests/multiset_test.cc -o multiset_test $(TEST_LIBS)
	./multiset_test

gcov_report: test
	lcov -t "./test" -o test.info --no-external -c -d ./
	genhtml -o report test.info
	open report/index.html


format:
	clang-format -i -style=google tests/*.cc *.h
	clang-format -n -style=google tests/*.cc *.h


clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css *.exe
	rm -rf s21_matrix_oop *.dSYM *.info test report/ .DS_Store
	rm -rf ../.DS_Store map_test test_array test_vector test_list test_stack test_queue set_test multiset_test
