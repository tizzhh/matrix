LFLAGS=-lcheck -L. -ls21_matrix -lsubunit -lm
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11
GCOV_FLAGS=-lgcov --coverage
CC=gcc

.PHONY: clean all rebuild

all: s21_matrix.a test

test: libs21_matrix.a tests.o
	$(CC) $^ $(LFLAGS) -o $@

gcov_report: s21_matrix.c tests.c libs21_matrix.a
	$(CC) $(CFLAGS) $^ $(LFLAGS) $(GCOV_FLAGS)
	./a.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

libs21_matrix.a: s21_matrix.a
	mv s21_matrix.a libs21_matrix.a

s21_matrix.a: s21_matrix.o
	ar -rcs $@ $^

s21_matrix.o: s21_matrix.c
	$(CC) -c $(CFLAGS) $^

tests.o: tests.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o test gcov_report *.gcda *.gcno coverage.info *.a a.out

rebuild: clean all
