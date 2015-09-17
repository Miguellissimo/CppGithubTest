# specify used compiler and flags
ifndef CXX
CXX = g++
endif

CFLAGS = -std=c++14 -Wall
CATCH_PATH = tests/catch.hpp
CPP_FILES := $(wildcard src/*.cpp)

all: debug

release: 
	cd src
	$(CXX) $(CFLAGS) $(CPP_FILES) -o main

debug:
	cd src
	$(CXX) $(CFLAGS) -g -O0 $(CPP_FILES) -o main

test: 
ifeq ("$(wildcard $(CATCH_PATH))","")
	wget -P tests/ https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
endif
	$(CXX) $(CFLAGS) tests/tests.cpp -o tester
	./tester

clean:
	rm -f *.o tester main

run:
	./main