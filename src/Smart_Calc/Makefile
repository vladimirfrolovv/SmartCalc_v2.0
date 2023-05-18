CC= g++ -std=c++17
CFLAGS=  -Wall -Werror -Wextra --coverage -g
OS = $(shell uname)
ifeq ($(OS), Linux)
	GTEST_FLAGS = -lgtest -lgtest_main -lm -pthread -lrt -lsubunit
else
	GTEST_FLAGS = -lgtest -lgtest_main
endif

all: install

to_style:
	clang-format -style=google -i Model/*.cc Model/*.h View/*.cc View/*.h Controller/*.cc Controller/*.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dvi:
	doxygen 
	open html/index.html


install: 
	mkdir Cmake
	cd Cmake/ && cmake ../CMakeLists.txt && make
	
open:
	open Cmake/CmakeSmartCalc.app

uninstall:
	rm -rf Cmake

dist:
	mkdir SmartCalcCpp
	cp -r Model/* View/* Controller/* CMakeLists.txt tests/ Makefile
	tar -cvzf dist.tar.gz SmartCalcCpp
	-rm -rf SmartCalcCpp


test: clean
	$(CC) $(CFLAGS)  tests/test.cc Controller/controller.cc Model/model.cc -o test $(GTEST_FLAGS)
	./test


gcov_report: test
	./test
	lcov -t "test" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov *.a
	open ./report/index-sort-f.html

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.out *.info report Cmake html dist.tar.gz SmartCalcCpp

rebuild: clean all 
