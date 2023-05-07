CC=gcc -std=c11 -g
CFLAGS=-Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRCS=$(wildcard s21_*.c)
OBJS=$(SRCS:.c=.o)
TESTSFLAGS_MAC= -lcheck 
# -lpthread -lsubunit -lrt -lm
LIB_NAME=smart_calc

all: install

to_style:
	clang-format -style=google -i *.c *.cpp *.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dvi:
	doxygen 
	open html/index.html

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

install: 
	mkdir Qmake
	cd Qmake/ && qmake ../Smart_Calc.pro && make 
	
open:
	open Qmake/Smart_Calc.app

uninstall:
	rm -rf Qmake

dist:
	mkdir SmartCalc
	cp -r *.c *.h *.cpp *.ui *.pro Makefile tests/ SmartCalc
	tar -cvzf dist.tar.gz SmartCalc
	-rm -rf SmartCalc


test: $(LIB_NAME).a 
	$(CC) $(CFLAGS) tests/test.c -L. $(LIB_NAME).a $(TESTSFLAGS_MAC) -o test
	./test


add_coverage_flag:
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage_flag test
	./test
	lcov -t "test" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov *.a
	open ./report/index-sort-f.html

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.out *.info report Qmake html dist.tar.gz SmartCalc

rebuild: clean all 
