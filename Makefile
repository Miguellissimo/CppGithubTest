# specify used compiler and flags
CXX = g++
CFLAGS = -std=c++14 -Wall
CATCH_PATH = tests/catch.hpp

all: debug

release: 
	cd src
	$(CXX) $(CFLAGS) *.cpp -o main

debug:
	cd src
	$(CXX) $(CFLAGS) -g -O0 *.cpp -o main

tests: 
ifeq ("$(wildcard $(CATCH_PATH))","")
	wget -P tests/ https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
endif
	$(CXX) $(CFLAGS) tests/tests.cpp -o tester

clean:
	rm -f *.o tester main

run:
	./main

test:
	./tester