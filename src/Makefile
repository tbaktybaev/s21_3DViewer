UNAME:=$(shell uname -s)
UNAME_ARCH:=$(shell uname -m)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	SYSFLAG=-D LINUX
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=CK_FORK=no leaks -quiet -atExit --
	SYSFLAG=-D APPLE
endif

ifeq ($(UNAME_ARCH), arm64)
	CHECK_HOME = /opt/homebrew/Cellar/check/0.15.2
	CFLAGS += -I$(CHECK_HOME)/include
	LDFLAGS += -L$(CHECK_HOME)/lib
	LFLAGS=-L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck -lm -lpthread
endif

CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage
MODULES = $(wildcard backend/*.c)
OBJECTS = $(patsubst %.c, %.o, $(MODULES))
SOURCESIB = backend/*.h backend/*.c front/*.cpp front/*.h test/test.c 
TESTS_SOURSES = $(wildcard *.check)
INST_DIR = 3DViewer
DIST_DIR = 3DViewer_v1
TEST_MODUlES = test_modules


all: install gcov_report

obj/%.o: backend/%.c
	mkdir -p obj
	gcc $(SYSFLAG) $(CFLAGS) -c $< -o $@

test: $(OBJECTS)
	gcc $(CFLAGS) ./test/test.c $(LFLAGS) backend/*.o -o test/$(TEST_MODUlES) 
	test/$(TEST_MODUlES) $(LFLAGS)
	@echo "» Unit test results:"
	@./test/$(TEST_MODUlES)
	@echo "» Clang test results:"
	cp ../materials/linters/.clang-format .
	clang-format --style=Google -n $(SOURCESIB)

gcov_report: test
	gcc --coverage $(CFLAGS) ./test/test.c $(LFLAGS) ./backend/*.c -o ./test/$(TEST_MODUlES)
	@./test/$(TEST_MODUlES)
	@echo "Generating Gcov report..."
	@mkdir -p gcov_report
	@mv *.gcno gcov_report && mv *.gcda gcov_report/
	@lcov --directory . --capture --output-file gcov_report/app.info
	@genhtml gcov_report/app.info --output-directory gcov_report/out
	@echo "Gcov report generated in gcov_report/out directory."
	@open gcov_report/out/index.html

install:
	@echo "Starting installation"
	@mkdir -p ../build
	@cd front && qmake && make &> /dev/null && make clean &> /dev/null && rm -rf Makefile && mv 3DViewer.app ../../build/$(INST_DIR).app 
	@cp -R ../build/$(INST_DIR).app ~/Desktop/$(INST_DIR).app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"
	@open ../build/3DViewer.app

uninstall: 
	rm -rf build*
	rm -rf ../build/* 
	rm -rf ~/Desktop/$(INST_DIR).app

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(INST_DIR).app ../dist
	@makeinfo manual.texi --html && mv manual_html/ ../dist/
	@cd ../dist && tar cvzf $(DIST_DIR).tgz *
	@cd ../dist && rm -rf $(INST_DIR).app manual_html
	@echo "The builded app was successfully archived"

format_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format --style=Google -n $(SOURCESIB)

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format --style=Google -i $(SOURCESIB)
	@echo "┏=======================┓"
	@echo "┃         Done          ┃"
	@echo "┗=======================┛"

valgrind_check: test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log_file="unit_tests_vg.log" \
	-v verbose -q --quiet -s tests/$(TEST_MODUlES)
	@echo "┏=========================================┓"
	@echo "┃        Valgrind check is over           ┃"
	@echo "┃       logs have been generated          ┃"
	@echo "┗=========================================┛"
	
dvi:
	makeinfo manual.texi --html
	open ./manual_html/index.html 

dvi_clean:
	rm -rf manual_html

clean:
	rm -rf *.a *.o *.out *.cfg fizz *.gc* *.info report $(DIST_DIR).tar $(INST_DIR) backend/*.o test/test_modules 
	rm -rf *.o *.out *.cfg *.tar manual_html .clang-format build* ../dist front/.qmake.stash gcov_report
	
rebuild: clean all 
