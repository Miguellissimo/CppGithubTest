# specify the used compiler
ifndef CXX
CXX = g++
endif

# specified compiler flags
YAML = lib/include/yaml-cpp
CFLAGS = -std=c++14 -Wall -I$(YAML)
LDFLAGS= -L./lib/ -lyaml-cpp -static
CATCH_PATH = tests/catch.hpp
CPP_FILES := $(wildcard src/*.cpp)
SRC_DIR = -I./src

all: debug

yaml:
ifeq ("$(wildcard $(YAML))","")
	#download library
	mkdir ./tmp
	wget -P ./tmp https://github.com/jbeder/yaml-cpp/archive/master.zip
	unzip ./tmp/master.zip -d ./tmp/
	mv ./tmp/yaml-cpp-master ./tmp/yaml-cpp
	rm ./tmp/master.zip
	
	#build as static library
	cd ./tmp/yaml-cpp && cmake -G "Unix Makefiles" -DBUILD_SHARED_LIBS=OFF
	cd ./tmp/yaml-cpp && make
	
	# move needed files
	mkdir -p ./lib/include
	mkdir ./lib/include/yaml-cpp
	mv ./tmp/yaml-cpp/libyaml-cpp.a ./lib
	mv ./tmp/yaml-cpp/include/* ./lib/include/yaml-cpp/yaml-cpp
	mv ./lib/include/yaml-cpp/yaml-cpp/yaml.h ./lib/include/yaml-cpp/yaml.h
	
	# cleanup
	rm -rf ./tmp
endif

release: yaml
	$(CXX) $(CFLAGS) $(CPP_FILES) -o main $(LDFLAGS)

debug: yaml
	$(CXX) $(CFLAGS) -g -O0 $(CPP_FILES) -o main $(LDFLAGS) -lyaml-cpp

test: 
ifeq ("$(wildcard $(CATCH_PATH))","")
	wget -P tests/ https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
endif
	$(CXX) $(CFLAGS) $(SRC_DIR) tests/tests.cpp -o tester $(LDFLAGS) -lyaml-cpp
	./tester

clean:
	rm -f *.o tester main
	rm -rf ./lib/*
	rm -rf ./tmp

run:
	./main