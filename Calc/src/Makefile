# #------------> Опции компилятора
FLAGS_MACOS = -L $(shell brew --prefix)/lib -lcheck
SLFLAGS = -lcheck -lsubunit 
MACOS_FLAG = 0
LEAK_TEST_TOOL = valgrind

# флаги специальных библиотек для сборки на макос
ifeq ($(shell uname), Darwin)
SLFLAGS = $(FLAGS_MACOS)
LEAK_TEST_TOOL = leak
endif

CC=gcc # компилятор
LFLAGS=-g # для сборки с отладочной информацией
LIBFLAGS=-lm # для линковки c математической либой
# LIBFLAGS = -lpthread -pthread -lrt -lm
CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic # для обработки ошибок
GCOVFLAGS=--coverage -fprofile-arcs -ftest-coverage # для анализа покрытия
INSTALL_DIR=calculator# Папка с программой


all: clean rebuild

rebuild: basic_build

basic_build: install test gcov_report dvi

s21_calc_v1.0.a: 
	$(CC) -c  $(CFLAGS) $(LFLAGS) SmartCalc/*.c deposit/*.c credit/*.c
	ar rc s21_calc_v1.0.a *.o

install: s21_calc_v1.0.a
	mkdir -p $(INSTALL_DIR)
	cd $(INSTALL_DIR) && cmake ../cpp && make

open_app:
	$(INSTALL_DIR)/cpp

dist:
	@rm -rf s21_calc_v1.0.tar
	@mkdir -p dist
	@cd .. && cp -r src dist && cp README.md dist
	@cd .. && mv dist src 
	@tar -zcf s21_calc_v1.0.tar dist 
	@rm -rf dist
	@echo "Архив с дистрибутивом программы создан в папке src/s21_calc_v1.0.tar"

uninstall:
	rm -rf $(INSTALL_DIR)

dvi:
	@doxygen dvi/Doxyfile > /dev/null 2>&1
	@open dvi/dvi_report/index.html

test: 
	$(CC) $(CFLAGS) $(LFLAGS) tests/*.c SmartCalc/*.c deposit/*.c credit/*.c s21_calc_v1.0.a $(SLFLAGS) $(LIBFLAGS) -o test -g
	@./test

gcov_report: all test
	$(CC) $(CFLAGS) $(LFLAGS) tests/*.c SmartCalc/*.c deposit/*.c credit/*.c s21_calc_v1.0.a $(SLFLAGS) $(LIBFLAGS) -o s21_gcov $(GCOVFLAGS)
	@./s21_gcov
	@lcov -t "gcov_report" -o s21_gcov_report.info -c -d .
	@lcov -r s21_gcov_report.info '*/tests/*' -o s21_gcov_report.info
	@genhtml -o s21_report s21_gcov_report.info
	@open s21_report/index.html > /dev/null 2>&1

clean: clean_obj clean_s21_report clean_dvi_report uninstall
	rm -rf *.so *.out report *.info *.txt *.cmake test *.gch *.pdf s21_gcov *.gcno *.gcda  
	rm -rf  *.html *.css *.tar

clean_obj:    
	rm -f *.a
	rm -f *.o

clean_s21_report:
	rm -rf report s21_report

clean_dvi_report:
	rm -rf dvi/dvi_report

leak_test:
	@make $(LEAK_TEST_TOOL)

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./test

clang:
	@clang-format -n SmartCalc/*.c deposit/*.c credit/*.c SmartCalc/*.h deposit/*.h credit/*.h cpp/*.cpp cpp/*.h tests/*.c tests/*.h

clang-fix:
	@clang-format -i SmartCalc/*.c deposit/*.c credit/*.c SmartCalc/*.h deposit/*.h credit/*.h cpp/*.cpp cpp/*.h tests/*.c tests/*.h

leak:
	@CK_FORK=no leaks --atExit -- ./test | grep LEAK


## Проверить?????
cpp:
	@cppcheck --enable=all --suppress=missingIncludeSystem tests/*.c *.h SmartCalc/*.c *.h deposit/*.c *.h credit/*.c *.h
	@cppcheck --enable=all --suppress=missingIncludeSystem --check-config gui_qt_sources *.cpp *.h

# #--->  исключения для аналогичных имён файлов 
.PHONY: make clean cppcheck style memcheck test gcov_report open_report cpp valgrind tar dist dvi install uninstall build rebuild leak